#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include "headers/function.hpp"
#include "headers/newton_raphson.hpp"
#include "headers/newton_raphson_modified.hpp"
#include "headers/secant.hpp"
#include "headers/csv_functions.hpp"
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
    else if (argc == 2) {
        if (std::strcmp(argv[1],"--help")==0){
            std::cout << "\nCalculadora de zeros de raízes\n";
            std::cout << "------------------------------\n";
            std::cout << "Comando correto\n";
            std::cout << "./main <x0> <x1> <a> <episilon1> <episilon2> <optional flags>\n\n";
        }
        else {
            std::cout << "Utilize a flag --help para saber o comando correto de inserção por linha de comando.\n";
        }
        return 1;
    }
    else {
        // "atof" function transform char variables to double
        x0 = atof(argv[1]);
        x1 = atof(argv[2]);
        a = atof(argv[3]);
        episilon1 = atof(argv[4]);
        episilon2 = atof(argv[5]);
    }
    pair<double, map<int, vector<double>>> nr = newton_raphson(func, derivative, x0, a, episilon1, episilon2);
    to_csv(nr,"newton_raphson");
    pair<double, map<int, vector<double>>> nm = newtonModified(func, derivative, x0, a, episilon1, episilon2);
    pair<double, map<int, vector<double>>> sc = secant(func, x0, x1, a, episilon1, episilon2);
    std::string scriptLibreOffice = "interface_final.ods"; 
    //openLO(scriptLibreOffice);
    return 0;
}
