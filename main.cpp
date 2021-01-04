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
    std::vector<std::shared_ptr<Symbol>> symbols;


    std::string entrada = "12 div 12";
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