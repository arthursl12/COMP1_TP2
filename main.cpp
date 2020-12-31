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
        Gramatica g;
        cria_gram_7(g);

        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>("b"));
        std::cout << (parser(entrada, g)) << std::endl;

        cria_gram_7(g);

        entrada.clear();
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>("b"));
        std::cout << (parser(entrada, g)) << std::endl;

        cria_gram_7(g);

        entrada.clear();
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>("b"));
        std::cout << (parser(entrada, g)) << std::endl;
    // print_action_goto_manual(tabAction, tabGoto);


    // std::string entrada = "12+12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada);

    // std::cout << std::endl;
    // entrada = "12+ +12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada);

    // std::cout << std::endl;
    // entrada = "12 <> (1.1 + -1.001E1)";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada);
    return 0;
    
}