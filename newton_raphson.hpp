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
pair<double, map<int, vector<double>>> newton_raphson (	double (*f) (double),
						double (*df) (double),
						double x0, double a,
						double episilon1,
						double episilon2){
    map<int, vector<double>> Map_NR;
	double root;
	double x1;
	int iter = 0;
	//começamos do x0 e inserimos a primeira iteracao no Mapa
	Map_NR.insert(
      pair<int, vector<double>>(iter, {x0, func(x0, a), derivative(x0, a), x0}));
	//checamos a condição inicial
	if (abs(func(x0, a)) < episilon1) { // condição inicial
    return make_pair(x0, Map_NR);
  }
	//repetimos
	while (1){
		iter++;
		double fx = func(x0, a); //calculando funcao no ponto 
		double fpx = func(x0, a); //calculando derivada da funcao no ponto
		double x = x0 - fx/fpx;  // calculando a raiz aproximada
   		double er = abs(x - x0) / abs(x0); // calculando o erro relativo
		Map_NR.insert(pair<int, vector<double>>(iter, {x0, a, fx, fpx, er})); // inserindo esses valores no mapa
		if (abs(fx) < episilon1 || abs(x - x0) < episilon2 || iter > MAX_ITER){ // condições de parada 
			return make_pair(x, Map_NR);
		}	
		x0 = x; // se ainda não paramos, continuamos e atualizamos o valor de x0 para a nova raiz aproximada
	}}
