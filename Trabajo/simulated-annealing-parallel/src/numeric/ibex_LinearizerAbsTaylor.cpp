/* ============================================================================
 * I B E X - AbsTaylor linearizer
 * ============================================================================
 *
 * Author(s)   : Ignacio Araya, Victor Reyes
 * Created     : May 2021
 * Updated     : May 2021
 * ---------------------------------------------------------------------------- */

#include "ibex_LinearizerAbsTaylor.h"
#include "ibex_SimulatedAnnealing.h"
#include "ibex_ExtendedSystem.h"
#include "ibex_Random.h"
#include "ibex_Exception.h"
#include "ibex_NormalizedSystem.h"
#include <iostream>
#include <vector>
#include <sys/wait.h>
#include <unistd.h> 
#include <mutex>
#include "/usr/include/pthread.h"

using namespace std;

namespace ibex {

struct ThreadArgs {
    IntervalVector box;
    System sys;
    Vector best_expansion_point;
    double best_expansion_fobj;
    pthread_mutex_t mtx;
};

void* v1_thread(void* args) {
    ThreadArgs* data = static_cast<ThreadArgs*>(args);
    SimulatedAnnealing SA(data->box, data->sys);
    std::pair<Vector, double> result = SA.v1(data->box);
    pthread_mutex_lock(&(data->mtx));
    if (result.second < data->best_expansion_fobj) {
        data->best_expansion_point = result.first;
        data->best_expansion_fobj = result.second;
    }
    pthread_mutex_unlock(&(data->mtx));
    return NULL;
}

namespace {
	class Unsatisfiability : public Exception { };
	class NoExpansionPoint : public Exception { };
}

LinearizerAbsTaylor::LinearizerAbsTaylor(const System& _sys, point_policy point):
		Linearizer(_sys.nb_var), sys(_sys),
			m(sys.f_ctrs.image_dim()), goal_ctr(-1 /*tmp*/),
			lp_solver(NULL), point(point) {

	if (dynamic_cast<const ExtendedSystem*>(&sys)) {
		((int&) goal_ctr)=((const ExtendedSystem&) sys).goal_ctr();
	}

}

LinearizerAbsTaylor::~LinearizerAbsTaylor() {

}

int LinearizerAbsTaylor::linearize(const IntervalVector& box, LPSolver& _lp_solver)  {
	lp_solver = &_lp_solver;
	IntervalVector box2(n*2);
	for(int i=0;i<n;i++)
		box2[i]=box[i];
	//initialize auxiliary variables u_i
	for(int i=0;i<n;i++)
		box2[n+i]=Interval(-box2[i].mag(), box2[i].mag());
	lp_solver->set_bounds(box2);
	return linear_restrict(box);
}

int LinearizerAbsTaylor::linear_restrict(const IntervalVector& box) {
    Vector exp_point(box.size());
    if (point == MID)
        exp_point = box.mid();
	else if (point == Simulated_Annealing_pthread){
        Vector best_expansion_point = box.mid();
        double best_expansion_fobj = std::numeric_limits<double>::max();
        pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

        ThreadArgs args = {box, sys, best_expansion_point, best_expansion_fobj, mtx};

        pthread_t t;
        pthread_create(&t, NULL, v1_thread, &args);
        pthread_join(t, NULL);

        pthread_mutex_lock(&mtx);
        exp_point = args.best_expansion_point;
        pthread_mutex_unlock(&mtx);
    }
    else if (point == Simulated_Annealing) {
		int NUM_PROCESSES = 5;
		pid_t pid[NUM_PROCESSES];
		int pipefd[2];
		double best_fobj = std::numeric_limits<double>::max();
		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		
		
		for(int i=0; i<NUM_PROCESSES; i++){
			pid[i] = fork();
			if (pid[i] < 0) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid[i] == 0) {
				close(pipefd[0]);
				SimulatedAnnealing SA(box, sys);
				std::pair<Vector, double> result = SA.v1(box);
				if (result.second < best_fobj) {
					best_fobj = result.second;
					ssize_t written = write(pipefd[1], &result, sizeof(result));
					if (written == -1 || written != sizeof(result)) {
						perror("write");
						exit(EXIT_FAILURE);
					}
				}
				close(pipefd[1]);
				exit(EXIT_SUCCESS);
			}
		}
		for(int i=0; i<NUM_PROCESSES; i++){
			int status;
			waitpid(pid[i], &status, 0);
		}

		close(pipefd[1]);
		std::pair<Vector, double> result = std::make_pair(Vector::zeros(box.size()), 0.0);
		ssize_t read_bytes = read(pipefd[0], &result, sizeof(result));
		if (read_bytes == -1 || read_bytes != sizeof(result)) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		exp_point = result.first;
    }
    else if (point == RANDOM){
        for (int i = 0 ; i < box.size() ; i++)
            exp_point[i] = RNG::rand(box[i].lb(),box[i].ub());
    }

	BitSet active=sys.active_ctrs(box);
	if (active.empty()) return 0;

	try {

		IntervalMatrix J=sys.f_ctrs.jacobian(box,active);
		//IntervalMatrix J=sys.active_ctrs_jacobian(box);  // --> better with SystemBox

		if (J.is_empty()) return -1; // note: no way to inform that the box is actually infeasible

		IntervalVector g_mid(sys.f_ctrs.eval_vector(exp_point,active));
		if (g_mid.is_empty()) return -1;

		// total number of added constraint
		// may be less than active.size() if
		// a constraint was not detected as inactive
		int count=0;
		int c; // constraint number

		for (int i=0; i<active.size(); i++) {
			c=(i==0? active.min() : active.next(c));

			try {
				if (sys.ops[c]==EQ && c!=goal_ctr)
					// in principle we could deal with linear constraints
					return -1;
				else if (c==goal_ctr || sys.ops[c]==LEQ || sys.ops[c]==LT)
					count += linearize_leq_mid(box,exp_point, J[i],g_mid[i]);
				else
					count += linearize_leq_mid(box, exp_point, -J[i],-g_mid[i]);
			} catch (LPException&) {
				return -1;
			} catch (Unsatisfiability&) {
				return -1;
			}
		}

		//adding constraints: -(xi - xi_mid) <= Ui, (xi - xi_mid) <= Ui
		for(int i=0; i<n; i++){
			Vector a=Vector::zeros(2*n);
			a[i]=-1.0;
			a[n+i]=-1.0;

			Vector a2=Vector::zeros(2*n);
			a2[i]=1.0;
			a2[n+i]=-1.0;


			lp_solver->add_constraint(a, LEQ, -exp_point[i] );
			lp_solver->add_constraint(a2, LEQ, exp_point[i] );
			count +=2;
		}

		return count;
	} catch(NoExpansionPoint&) {
		return -1;
	}

}


int LinearizerAbsTaylor::linearize_leq_mid(const IntervalVector& box, const Vector& point, const IntervalVector& dg_box, const Interval& g_mid) {
	Vector a(2*n); // vector of coefficients

	// ========= compute matrix of coefficients ===========
	// Fix each coefficient to the lower/upper bound of the
	// constraint gradient, depending on the position of the
	// corresponding component of the corner and the
	// linearization mode.
	for (int j=0; j<n; j++){
		a[j]=dg_box[j].mid();
	}

	for (int j=n; j<2*n; j++){
		a[j]=(dg_box[j-n]-a[j-n]).mag();
	}

	// =====================================================
    Vector aa=a;
	aa.resize(box.size());
	Interval rhs = -g_mid + aa*point - lp_solver->tolerance();

	double b = rhs.lb() ;

	// may throw Unsatisfiability and LPException
	return check_and_add_constraint(box,a,b);
}

int LinearizerAbsTaylor::check_and_add_constraint(const IntervalVector& box, const Vector& a, double b) {

	Interval ax=a*box; // for fast (in)feasibility check

	// ======= Quick (in)feasibility checks
	//                 a*[x] <= rhs ?
	if (ax.lb()>b)
		// the constraint is not satisfied
		throw Unsatisfiability();
	else if (ax.ub()<=b) {
		// the (linear) constraint is satisfied for any point in the box
		return 0;
	} else {
		//cout << "add constraint " << a << "*x<=" << b << endl;
		lp_solver->add_constraint(a, LEQ, b);
		return 1;
	}
}

} // end namespace
