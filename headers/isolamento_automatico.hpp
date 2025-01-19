#include <cmath>
#include <vector>
#include <map> 
#include <utility>

std::pair <double, double> Bisseccao (double (*func) (double,double),
                                      double a,
                                      double inf,
                                      double sup,
                                      double epsilon,
                                      int iter) {
	double x,fx;
	double finf = func(inf, a);
	double fsup = func(sup, a);
    double intervX = abs(sup-inf);
    while (func(inf, a) > epsilon) {
        x = (inf+sup)/2;
        if (intervX <= epsilon || iter >= 1000) return {inf, x};
        if (finf*fx > 0){
			inf = x;
			finf = fx;
		} else {
			sup = x;
			fsup = x;
		}
		iter++;
		intervX = intervX/2;
    }
    return {inf, x};
}
