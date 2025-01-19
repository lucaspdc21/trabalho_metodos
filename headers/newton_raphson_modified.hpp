#include <iostream>
#include <cmath>
#include <vector>
#include <map> 
#include <utility>
#define constA          1.0
#define iterMax         10000
using namespace std;
pair<double, map<int, vector<double>>> newtonModified(double (*func) (double, double), 
                                                              double (*derivative) (double, double), 
                                                              double x0, 
                                                              double a, 
                                                              double epsilon1,
                                                              double epsilon2)
{   
    map<int, vector<double>> Map_NR_mod;
    int iter = 0;
    double dx0 = derivative(x0,a);
    if (dx0 == 0){
      //se derivada == 0, metodo para. 
      return make_pair(-404.404404404, Map_NR_mod); 
    }
    Map_NR_mod.insert(
      pair<int, vector<double>>(iter, {x0, func(x0, a), dx0, x0}));
    double Dx0 = 1 / dx0; // esta é a diferença deste método para o método de newton_raphson normal
    //ou seja, a função de iteração é somente x - f(x)/f'(x0) ao invés de ser x - f(x)/f'(x)
    if (abs(func(x0,a))< epsilon1){    
        return make_pair(x0, Map_NR_mod);
    }
    else{
        double x; 
        while (1){
        iter++;
        double fx = func(x0,a); //calculando funcao no ponto 
        x = x0 - fx * Dx0; 
        double er = abs(x - x0) / abs(x0); // calculando o erro relativo
        Map_NR_mod.insert(pair<int, vector<double>>(iter, {x0, a, fx, dx0, er})); // inserindo esses valores no mapa
        if ((abs(func(x,a)) < epsilon1) || (er < epsilon2) || (iter >= iterMax) )
                return make_pair(x, Map_NR_mod);
        x0 = x; // se ainda não paramos, continuamos e atualizamos o valor de x0 para a nova raiz aproximada
    }}}
