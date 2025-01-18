#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "headers/function.hpp"
#include "headers/newton_raphson.hpp"
#include "headers/newton_raphson_modified.hpp"
#include "headers/secant.hpp"
#include "headers/csv_functions.hpp"

// struct criada para armazenar os resultados de cada método
struct Result {
    std::string method;
    double a;
    double r_final;
    double fx;
    double error;
    int iterations;

    Result(const std::string& method, double a, double r_final, double fx, double error, int iterations)
        : method(method), a(a), r_final(r_final), fx(fx), error(error), iterations(iterations) {}
};

// Printa resultados individuais
void printResults(const std::string& method, const std::pair<double, std::map<int, std::vector<double>>>& results) {
    std::cout << "Resultados do método " << method << ":\n";
    for (const auto& [iter, values] : results.second) {
        std::cout << "Iteração " << iter << ": ";
        for (const auto& value : values) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Raiz final: " << results.first << "\n\n";
}

// Printa o quadro comparativo
void printComparison(const std::vector<Result>& comparisons) {
    std::cout << "Quadro Comparativo:\n";
    std::cout << "Método\t\ta\tRaiz Final\tf(x)\tErro em x\tIterações\n";
    for (const auto& result : comparisons) {
        std::cout << result.method << "\t" << result.a << "\t" << result.r_final << "\t" << result.fx << "\t" << result.error << "\t" << result.iterations << "\n";
    }
}

int main(int argc, char* argv[]) {
    double x0, x1, episilon1, episilon2;
    int n;
    std::vector<double> a_values;

    // --help flag (could be done better, but this will work)
    if (argc < 2) {
        std::cout << "Input Mode \n" << " \"Use ./main --help\" para utilizar o modo de input direto da linha de comando\n\n";
        std::cout << "x0: ";
        std::cin >> x0;
        std::cout << "x1: ";
        std::cin >> x1;
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
    } else if (argc == 2) {
        if (std::strcmp(argv[1], "--help") == 0) {
            std::cout << "\nCalculadora de zeros de raízes\n";
            std::cout << "------------------------------\n";
            std::cout << "Comando correto\n";
            std::cout << "./main <x0> <x1> <episilon1> <episilon2> <n> <a1> <a2> ... <an>\n\n";
        } else {
            std::cout << "Utilize a flag --help para saber o comando correto de inserção por linha de comando.\n";
        }
        return 1;
    } else {
        // "atof" function transform char variables to double
        x0 = atof(argv[1]);
        x1 = atof(argv[2]);
        episilon1 = atof(argv[3]);
        episilon2 = atof(argv[4]);
        n = atoi(argv[5]);
        a_values.resize(n);
        for (int i = 0; i < n; ++i) {
            a_values[i] = atof(argv[6 + i]);
        }
    }

    // Vetor utilizado para armazenar comparações
    std::vector<Result> comparisons;

    for (double a : a_values) {
        const char* header_nr = "iteração,x0, a , f(x) , f'(x), erro relativo\n";
        pair<double, map<int, vector<double>>> nr = newton_raphson(func, derivative, x0, a, episilon1, episilon2);
        to_csv(nr, header_nr, "newton_raphson_a_" + std::to_string(a));
        // exibi os resultados individuais e armazena no vetor de comparações
        printResults("Newton-Raphson", nr);
        comparisons.push_back(Result("Newton-Raphson", a, nr.first, func(nr.first, a), abs(nr.first - x0), nr.second.size()));

        const char* header_nm = "iteração, x0, a, f(x), f'(x0), erro relativo \n";
        pair<double, map<int, vector<double>>> nm = newtonModified(func, derivative, x0, a, episilon1, episilon2);
        to_csv(nm, header_nm, "newton_raphson_modified_a_" + std::to_string(a));

        printResults("Newton-Raphson Modificado", nm);
        comparisons.push_back(Result("Newton-Raphson Modificado", a, nm.first, func(nm.first, a), abs(nm.first - x0), nm.second.size()));

        const char* header_sc = "iteração, x0, f(x0) , x1, f(x1), erro relativo \n";
        pair<double, map<int, vector<double>>> sc = secant(func, x0, x1, a, episilon1, episilon2);
        to_csv(sc, header_sc, "secant_a_" + std::to_string(a));
         
        printResults("Secante", sc);
        comparisons.push_back(Result("Secante", a, sc.first, func(sc.first, a), abs(sc.first - x0), sc.second.size()));
    }

    printComparison(comparisons);

    std::string scriptLibreOffice = "interface_final.ods"; 
    //openLO(scriptLibreOffice);
    return 0;
}
