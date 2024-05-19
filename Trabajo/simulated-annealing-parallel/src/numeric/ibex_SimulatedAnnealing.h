#include <vector>
#include "ibex_IntervalVector.h"
#include "ibex_System.h"
#include <iostream> 
namespace ibex {
    class SimulatedAnnealing{
        public:
            SimulatedAnnealing(const IntervalVector& box, const System& sys);
            double f_obj(const IntervalVector& x, int ctr) const;
            std::pair<Vector, double> v1(const IntervalVector& box);
        private:
            const IntervalVector& box;
            const System& sys;
            
    };
}