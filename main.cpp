#include <iostream>
#include <string>

#include "lex.h"
#include "conj.h"
#include "gram.h"
#include "utils.h"
#include "tests/gram_exemplos.h"
#include "tests/closure_goto.h"
#include "tests/conj_itens.h"
#include "tests/action_goto.h"

int main(int argc, char* argv[]){
    // Carrega a gramática
    Gramatica G;        // TODO

    // Entrada vinda do arquivo
    std::string input = "entrada.in";
    std::vector<std::string> programas;
    inputFile(programas, input);

    // Analisa cada linha (programa) do arquivo
    for (std::string program : programas){
        if (program == ",,print"){
            TabelaAction t1;
            TabelaGoto t2;
            tabActionGoto(t1, t2, G, true);
            continue;
        }

        std::vector<std::shared_ptr<Symbol>> symbols;
        symbols.clear();
        findTokens(program, symbols);
        parser(symbols, G);
    }

    std::vector<std::shared_ptr<Symbol>> symbols;

    std::string entrada = "1+(-var2)";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada, symbols);

    std::cout << std::endl;
    entrada = "12 cos 12";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada, symbols);

    // std::cout << std::endl;
    // entrada = "12 <> (1.1 + -1.001E1)";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada, symbols);
    // std::vector<std::shared_ptr<Symbol>> symbols;


    // std::string entrada = "12+12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada, symbols);

    // std::cout << std::endl;
    // entrada = "12+ +12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada, symbols);

    // std::cout << std::endl;
    // entrada = "12 <> (1.1 + -1.001E1)";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada, symbols);
    return 0;
    
}