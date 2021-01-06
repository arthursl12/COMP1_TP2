#include <iostream>
#include <string>

#include "lex.h"
#include "conj.h"
#include "gram.h"
#include "utils.h"
#include "tabelas.h"
#include "parser.h"
#include "tests/gram_exemplos.h"
#include "tests/closure_goto.h"
#include "tests/conj_itens.h"
#include "tests/action_goto.h"

int main(int argc, char* argv[]){
    // Carrega a gramática
    Gramatica G;        // TODO


    
    // Inicialização e entrada do usuário
    std::cout << "==========AVALIADOR DE EXPRESSÕES==========" << std::endl;
    std::cout << "Digite a expressão: ";
    std::string entrada = "12+12,sin 90";
    // std::string entrada;
    // std::getline(std::cin, entrada);

    bool exprToProcess = true;

    if (entrada == "print"){
        TabelaAction t1;
        TabelaGoto t2;
        tabActionGoto(t1, t2, G, true);
        exprToProcess = false;
    }

    int left = 0;
    int right = 0;
    while(exprToProcess){
        std::vector<std::shared_ptr<Symbol>> symbols;
        symbols.clear();
        exprToProcess = findTokens(entrada, symbols, left, right);
        parser(symbols, G); 
    }
    


    // std::vector<std::shared_ptr<Symbol>> symbols;

    // std::string entrada = "1+(-var2)";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada, symbols);

    // std::cout << std::endl;
    // entrada = "12 cos 12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada, symbols);

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