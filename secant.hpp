#include <iostream>
#include <cmath>
#include <vector>
#include <map> 
#include <utility>
#define MAX_ITER 100
using namespace std;

// f(d) = a*ed – 4*d2
//f(x) here
double func (double x,double a){
   return a * std::exp(x) - 4*(x*x);
}
//g(x) = derivative of f(x)
double derivative (double x,double a){
   return a * std::exp(x) - 8*x;
}

pair<double, map<int, vector<double>>> secant (	double (*f) (double),
				double x0,
				double x1,
				double a,
				double episilon1,
				double episilon2){
	map<int, vector<double>> Map_SEC;
	double root,x2;
	double fx0 = func(x0, a); 
	double fx1 = func(x1, a); 
	int iter = 0;
	if (abs(fx0)<episilon1){
		return make_pair(x0, Map_SEC);
	}
	if ((abs(fx1)<episilon1)||(abs(x1-x0)<episilon2)){
		return make_pair(x1, Map_SEC);
	}
	while (1){
		iter++;
		double fx0 = func(x0, a); 
		double fx1 = func(x1, a); 
		x2 = (x0*fx1 - x1*fx0)/(fx1 - fx0); //mudei pra formula do livro só porque... sim? acho ela mais entendível. 
		double absDif = abs(x2-x1);
		double funcx2 = func(x2, a);
		double erro_relativo = abs(x1 - x0) / abs(x1);
		Map_SEC.insert(
        pair<int, vector<double>>(iter, {x0,fx0,x1, fx1, erro_relativo}));
		if (((abs(funcx2))<episilon1)||(absDif<episilon2)||(iter>=MAX_ITER)){
			return make_pair(x2, Map_SEC);
		}
		x0 = x1;
		x1 = x2;
	}
}
