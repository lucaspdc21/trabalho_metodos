#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include "headers/function.hpp"
#include "headers/newton_raphson.hpp"
#include "headers/newton_raphson_modified.hpp"
#include "headers/secant.hpp"
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
int main(int argc, char* argv[]) {
    double x0,x1,a,episilon1,episilon2;
    // --help flag (could be done better, but this will work)
    if (argc < 2){
        std::cout   << "Input Mode \n" << " \"Use ./main --help\" para utilizar o modo de input direto da linha de comando\n\n";
        std::cout   << "x0: ";
        std::cin    >> x0;
        std::cout   << "x1: ";
        std::cin    >> x1;
        std::cout   << "a: ";
        std::cin    >> a;
        std::cout   << "episilon1: ";
        std::cin    >> episilon1;
        std::cout   << "episilon2: ";
        std::cin    >> episilon2;
    }
    if (argc == 2) {
        if (std::strcmp(argv[1],"--help")==0){
            std::cout << "\nCalculadora de zeros de raízes\n";
            std::cout << "------------------------------\n";
            std::cout << "Comando correto\n";
            std::cout << "./main <x0> <x1> <a> <episilon1> <episilon2> <optional flags>\n\n";
        }
        else {
            std::cout << "Utilize a flag --help para saber o comando correto de inserção por linha de comando.\n";
        }
    }
    else {
        // "atof" function transform char variables to double
        x0 = stod(argv[1]);
        x1 = stod(argv[2]);
        a = stod(argv[3]);
        episilon1 = stod(argv[4]);
        episilon2 = stod(argv[5]);

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
