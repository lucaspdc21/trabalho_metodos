#include <iostream>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <map>
void vec_to_file (std::vector<double> v,FILE* f){
	for (const auto x : v){
		fprintf(f, "%f,",x);
	}
	fprintf(f, "\n");
}
void to_csv(const pair<double,std::map<int, std::vector<double>>> p,const char* header_csv_method,std::string title = "example"){
	time_t timestamp;
	std::string name_file = "arquivos_csv/" + std::to_string(time(&timestamp)) + "_" + title + ".csv";
	std::cout << "File name: " << name_file << '\n';
	std::FILE* csv_file = std::fopen(name_file.c_str(),"w+");
	std::map func_map = std::get<1>(p);
	fprintf(csv_file,header_csv_method);
	for (const auto&[key,vec] : func_map){
		fprintf(csv_file, "%i,",key);
		vec_to_file(vec,csv_file);
		//printf("%i , %f, %f, %f, %f, %f\n",n,vec[1],vec[2],vec[3],vec[4],vec[5]);
	}
	fprintf(csv_file,"\nRaiz Final: ,%f",std::get<0>(p));
	std::fclose(csv_file);
}
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
