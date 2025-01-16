#include <iostream>
#include <cmath>
#include <vector>
#include <map> 
#include <utility>

#define constA          1.0
#define iterMax         100000
using namespace std;


pair<double, map<int, vector<double>>> newtonModified(double (*f) (double, double), double (*df) (double, double), double a, double x0, double epsilon1,double epsilon2) {   
    map<int, vector<double>> Map_NR_mod;
    int iter = 0;
    Map_NR_mod.insert(
        pair<int, vector<double>>(iter, {x0, f(x0, a), df(x0,a), x0}));
    double Dx0 = 1 / df(x0,a); // esta é a diferença deste método para o método de newton_raphson normal
    //ou seja, a função de iteração é somente x - f(x)/f'(x0) ao invés de ser x - f(x)/f'(x)
    if (abs(f(x0,a))< epsilon1){    
        return make_pair(x0, Map_NR_mod);
    }
    else{
        double x; 
        while (1){
            iter++;
            double fx = f(x0,a); //calculando funcao no ponto 
            x = x0 - fx * Dx0; 
            double er = abs(x - x0) / abs(x0); // calculando o erro relativo
            Map_NR_mod.insert(pair<int, vector<double>>(iter, {x0, a, fx, Dx0, er})); // inserindo esses valores no mapa
            if ((abs(f(x,a)) < epsilon1) || (x-x0 > epsilon2) || (iter >= iterMax) )
                return make_pair(x, Map_NR_mod);
            x0 = x; // se ainda não paramos, continuamos e atualizamos o valor de x0 para a nova raiz aproximada
        }
    }
}
