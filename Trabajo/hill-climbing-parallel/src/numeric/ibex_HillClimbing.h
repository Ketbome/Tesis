#include <vector>
#include "ibex_IntervalVector.h"
#include "ibex_System.h"
#include <iostream> 
namespace ibex {
    class HillClimbing{
        public:
            HillClimbing(const IntervalVector& box, const System& sys);
            double f_obj(const IntervalVector& x, int ctr) const;

            std::pair<Vector, double> v1(const IntervalVector& box);
            std::pair<Vector, double> v2(const IntervalVector& box);
            std::pair<Vector, double> v3(const IntervalVector& box);
            std::pair<Vector, double> v4(const IntervalVector& box);
        private:
            const IntervalVector& box;
            const System& sys;
            
    };
}