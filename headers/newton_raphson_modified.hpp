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
        pair<int, vector<double>>(iter, {x0, f(x0, a), NULL, NULL, df(x0,a), x0}));
    double dx0 = df(x0,a); // f'(x0)
    double Dx0 = 1 / dx0; // esta é a diferença deste método para o método de newton_raphson normal
    //ou seja, a função de iteração é somente x - f(x)/f'(x0) ao invés de ser x - f(x)/f'(x)
    if (abs(f(x0,a))< epsilon1){    
        return make_pair(x0, Map_NR_mod);
    }
    else{
        double x; 
        while (1){
            iter++;
            double fx0 = f(x0,a); //calculando funcao no ponto x0
            x = x0 - fx0 * Dx0; 
            double er = abs(x - x0) / abs(x0); // calculando o erro relativo
            double fx = f(x,a); // calculando a funcao no ponto x
            Map_NR_mod.insert(pair<int, vector<double>>(iter, {x, fx, x0, fx0, dx0, er})); // inserindo esses valores no mapa
            if ((abs(fx) < epsilon1) || (abs(x-x0) < epsilon2) || (iter >= iterMax) )
                return make_pair(x, Map_NR_mod);
            x0 = x; // se ainda nao paramos, continuamos e atualizamos o valor de x0 para a nova raiz aproximada
            //poderiamos fazer fx = fx0 e evitar o calculo da funcao no ponto x0 mais de uma vez, porem
            //preferimos repetir os calculos a cada iteracao para deixar o codigo mais explicito. 
        }
    }
}
