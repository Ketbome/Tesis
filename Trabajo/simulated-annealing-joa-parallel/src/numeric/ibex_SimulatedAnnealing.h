#include <vector>
#include "ibex_IntervalVector.h"
#include "ibex_System.h"
#include <iostream> 
namespace ibex {
    class SimulatedAnnealing{
        public:
            SimulatedAnnealing(const IntervalVector& box, const System& sys);
            double f_obj(const IntervalVector& x, int ctr) const;
            Vector fun_per(const Vector& X_B, const IntervalVector& box, int ctr);
            Vector fun_per2(const Vector& X_B, const IntervalVector& box, int ctr);
            Vector fun_per3(const Vector& X_B, const IntervalVector& box);
            std::pair<Vector, double> v1(const IntervalVector& box);
            std::pair<Vector, double> v2(const IntervalVector& box);
            std::pair<Vector, double> v3(const IntervalVector& box);
            std::pair<Vector, double> v4(const IntervalVector& box);
            std::pair<Vector, double> v5(const IntervalVector& box);
            std::pair<Vector, double> v6(const IntervalVector& box);
            std::pair<Vector, double> v7(const IntervalVector& box);
        private:
            const IntervalVector& box;
            const System& sys;
            
    };
}