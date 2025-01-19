#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iomanip> // formatação de saída
#include "headers/function.hpp"
#include "headers/newton_raphson.hpp"
#include "headers/newton_raphson_modified.hpp"
#include "headers/secant.hpp"
#include "headers/csv_functions.hpp"
#include "headers/outputFunctions.hpp"
#include "headers/isolamento_automatico.hpp"

int main(int argc, char* argv[]) {
    double x0, x1, episilon1, episilon2;
    int n;
    bool isolamento = true;
    std::vector<double> a_values;

    // --help flag (could be done better, but this will work)
    if (argc <= 2) {
        if (argc == 2) {
            if (std::strcmp(argv[1], "--help") == 0) {
                std::cout << "\nCalculadora de zeros de raízes\n";
                std::cout << "------------------------------\n";
                std::cout << "Modo input\n";
                std::cout << "./main.out\n";
                std::cout << "Caso deseje inserir os dados iniciais, utilize a flag -x\n";
                std::cout << "Exemplo: ./main.out -x\n\n";
                std::cout << "Modo argumento de terminal\n";
                std::cout << "./main <episilon1> <episilon2> <n> <a1> <a2> ... <an>\n";
                std::cout << "Utilize a flag -x para dar como entrada aproximações iniciais\n";
                std::cout << "Exemplo:./main -x <x0> <x1> <episilon1> <episilon2> <n> <a1> <a2> ... <an>\n\n";
                return 0;
            } else if (std::strcmp(argv[1], "-x") == 0) {
                isolamento = false;
                std::cout << "x0: ";
                std::cin >> x0;
                std::cout << "x1: ";
                std::cin >> x1;
            } else {
                std::cout << "Utilize a flag --help para saber o comando correto de inserção por linha de comando.\n";
                return 1;
            }
        }

        std::cout << "Input Mode \n" << " \"Use ./main --help\" para utilizar o modo de input direto da linha de comando\n\n";
        std::cout << "episilon1: ";
        std::cin >> episilon1;
        std::cout << "episilon2: ";
        std::cin >> episilon2;
        std::cout << "n (número de valores de a): ";
        std::cin >> n;
        a_values.resize(n);
        for (int i = 0; i < n; ++i) {
            std::cout << "a[" << i << "]: ";
            std::cin >> a_values[i];
        }
    } else {
        int ent = 0;
        if (std::strcmp(argv[1],"-x") == 0) {
            isolamento = false;
            ent = 3;
            x0 = atof(argv[2]);
            x1 = atof(argv[3]);
        }
        episilon1 = atof(argv[ent + 1]);
        episilon2 = atof(argv[ent + 2]);
        n = atoi(argv[ent + 3]);
        a_values.resize(n);
        for (int i = 0; i < n; ++i) {
            a_values[i] = atof(argv[ent + 4 + i]);
        }
    }

    // Vetor utilizado para armazenar comparações
    std::vector<Result> comparisons;

    for (double a : a_values) {
        if (isolamento) {
            pair <double, double> aprox = Bisseccao (func, a, -80, 5, 1, 0);
            x0 = aprox.first;
            x1 = aprox.second;
        }

        const char* header_nr = "iteração,x0, a , f(x) , f'(x), erro relativo\n";
        pair<double, map<int, vector<double>>> nr = newton_raphson(func, derivative, x0, a, episilon1, episilon2);
        to_csv(nr, header_nr, "newton_raphson_a_" + std::to_string(a));
        // exibi os resultados individuais e armazena no vetor de comparações
        printResults("Newton-Raphson", a, nr);
        comparisons.push_back(Result("Newton-Raphson", a, nr.first, func(nr.first, a), abs(nr.first - x0), nr.second.size()));

        const char* header_nm = "iteração, x0, a, f(x), f'(x0), erro relativo \n";
        pair<double, map<int, vector<double>>> nm = newtonModified(func, derivative, x0, a, episilon1, episilon2);
        to_csv(nm, header_nm, "newton_raphson_modified_a_" + std::to_string(a));

        printResults("Newton-Raphson Modificado", a, nm);
        comparisons.push_back(Result("Newton-Raphson Modificado", a, nm.first, func(nm.first, a), abs(nm.first - x0), nm.second.size()));

        const char* header_sc = "iteração, x0, f(x0) , x1, f(x1), erro relativo \n";
        pair<double, map<int, vector<double>>> sc = secant(func, x0, x1, a, episilon1, episilon2);
        to_csv(sc, header_sc, "secant_a_" + std::to_string(a));
         
        printResults("Secante", a, sc);
        comparisons.push_back(Result("Secante", a, sc.first, func(sc.first, a), abs(sc.first - x0), sc.second.size()));
    }

    printComparison(comparisons);

    std::string scriptLibreOffice = "interface_final.ods"; 
    //openLO(scriptLibreOffice);
    return 0;
}
