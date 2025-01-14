#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include "newton_raphson.hpp"
#include "newton_raphson_modified.hpp"
#include "secant.hpp"
using namespace std;
void openLO(const std::string& scriptPath) {
    // erro: Warning: failed to launch javaldx - java may not function correctly
    // TODO: procuarar uma solução para o erro acima
    std::string comando = "libreoffice --calc " + scriptPath + " &";
    int retorno = system(comando.c_str());
    if (retorno == 0) {
        std::cout << "LibreOffice Calc aberto com sucesso.\n";
    } else {
        std::cerr << "Erro ao abrir o LibreOffice Calc.\n";
    }
}

double func (double x,double a){
    return a * exp(x) - 4*(x*x);
}

double derivative (double x,double a){
    return a * exp(x) - 8*x;
}

int main(int argc, char* argv[]) {

    // --help flag (could be done better, but this will work)
    if (argc == 2 && strcmp(argv[1], "--help")==0) {
        cout << "\nCalculadora de zeros de raízes\n";
        cout << "------------------------------\n";
        cout << "Comando correto\n";
        cout << "./main <x0> <x1> <a> <episilon1> <episilon2>\n\n";
    }
    else {
        // "atof" function transform char variables to double
        double x0 = atof(argv[1]);
        double x1 = atof(argv[2]);
        double a = atof(argv[3]);
        double episilon1 = atof(argv[4]);
        double episilon2 = atof(argv[5]);

        // Saving the funcion results
        pair<double, map<int, vector<double>>> nr = newton_raphson(func, derivative, x0, a, episilon1, episilon2);
        pair<double, map<int, vector<double>>> nm = newtonModified(func, derivative, x0, a, episilon1, episilon2);
        pair<double, map<int, vector<double>>> sc = secant(func, x0, x1, a, episilon1, episilon2);

        // TODO: Update csv data
        std::string scriptLibreOffice = "interface_final.ods"; 
        openLO(scriptLibreOffice);
    }
    return 0;
}
