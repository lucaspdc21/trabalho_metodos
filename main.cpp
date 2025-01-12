#include <iostream>
#include <cstdlib> 
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


int main() {
    std::string scriptLibreOffice = "interface_final.ods"; 
    openLO(scriptLibreOffice);

    return 0;
}