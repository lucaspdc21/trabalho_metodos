#include <iostream>
#include <cmath>
#define MAX_ITER 100
double secant (	double (*func) (double),
				double x0,
				double x1,
				double episilon1,
				double episilon2){
	double root,x2;
	if (abs(func(x0))<episilon1){
		return x0;
	}
	if ((abs(func(x1))<episilon1)||(abs(x1-x0)<episilon2)){
		return x1;
	}
	int iter = 0;
	while (1){
		x2 = x1 - (func(x1)/((func(x1)-func(x0))/(x1-x0)));
		double absDif = abs(x2-x1);
		double funcx2 = func(x2);
		printf("iter: %i\na(k+1):%.4f\n|a(k+1)-a(k)|: %.4f\nf(a(k+1)):%.4f\n\n",iter,x2,absDif,funcx2);
		if ((abs(func(x2))<episilon1)||(absDif<episilon2)||(iter>=MAX_ITER)){
			root = x2;
			break;
		}
		x0 = x1;
		x1 = x2;
		iter++;
	}
	return root;
}