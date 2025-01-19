#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

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
void printResults(const std::string& method, double a, const std::pair<double, std::map<int, std::vector<double>>>& results) {
    std::cout << "Resultados do método " << method << " para a = " << a << ":\n";
    if (method == "Secante") {
        std::cout << std::setw(10) << "  Iteração" << std::setw(15) << "x0" << std::setw(15) << "f(x0)" << std::setw(15) << "x1" << std::setw(15) << "f(x1)" << std::setw(16) << "Erro Relativo\n"; // Adiciona o cabeçalho
    } else {
        std::cout << std::setw(10) << "  Iteração" << std::setw(15) << "x0" << std::setw(15) << "f(x)" << std::setw(15) << "f'(x)" << std::setw(16) << "Erro Relativo\n"; // Adiciona o cabeçalho
    }
    for (const auto& [iter, values] : results.second) {
        std::cout << std::setw(10) << iter;
        for (size_t i = 0; i < values.size(); ++i) {
            if (method == "Secante" || i != 1) { // Ignora a coluna 'a' para métodos que não são Secante
                std::cout << std::setw(15) << values[i];
            }
        }
        std::cout << "\n";
    }
    std::cout << "Raiz final: " << results.first << "\n\n";
}

// Printa o quadro comparativo
void printComparison(const std::vector<Result>& comparisons) {
    std::cout << "Quadro Comparativo:\n";
    std::cout << std::setw(30) << "Método" << std::setw(10) << "a" << std::setw(15) << "Raiz Final" << std::setw(15) << "f(x)" << std::setw(15) << "Erro em x" << std::setw(18) << "Iterações\n";
    for (const auto& result : comparisons) {
        std::cout << std::setw(29) << result.method << std::setw(10) << result.a << std::setw(15) << result.r_final << std::setw(15) << result.fx << std::setw(15) << result.error << std::setw(15) << result.iterations << "\n";
    }
}
