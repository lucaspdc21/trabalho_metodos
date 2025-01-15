#include <iostream>
#include <cmath>
#include <vector>
#include <map> 
#include <utility>
#define MAX_ITER 100
using namespace std; 

pair<double, map<int, vector<double>>> newton_raphson (double (*f) (double, double),
                                                       double (*df) (double, double),
                                                       double x0, double a,
                                                       double episilon1,
                                                       double episilon2){
    map<int, vector<double>> Map_NR;
    int iter = 0;
    //começamos do x0 e inserimos a primeira iteracao no Mapa
    Map_NR.insert(
        pair<int, vector<double>>(iter, {x0, f(x0, a), NULL, NULL, df(x0, a), x0}));
    //checamos a condição inicial
    if (abs(f(x0, a)) < episilon1) { // condição inicial
        return make_pair(x0, Map_NR);
    }
    double fx, fx0, fpx0, x, er;
    //repetimos
    while (1){
        iter++;
        fx0 = f(x0, a); //calculando funcao no ponto 
        fpx0 = f(x0, a); //calculando derivada da funcao no ponto
        x = x0 - fx0/fpx0;  // calculando a raiz aproximada
        er = abs(x - x0) / abs(x0); // calculando o erro relativo
        fx = f(x,a); 
        Map_NR.insert(pair<int, vector<double>>(iter, {x, fx, x0, fx0, fpx0, er})); // inserindo esses valores no mapa
        if ((abs(fx)) < episilon1 || abs(x - x0) < episilon2 || iter > MAX_ITER){ // condições de parada 
            return make_pair(x, Map_NR);
        }	
        x0 = x; // se ainda não paramos, continuamos e atualizamos o valor de x0 para a nova raiz aproximada
    }
}
