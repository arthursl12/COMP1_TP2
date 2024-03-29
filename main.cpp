#include <iostream>
#include <string>

#include "lex.h"
#include "conj.h"
#include "gram.h"
#include "tp.h"
#include "utils.h"
#include "tabelas.h"
#include "parser.h"
#include "tests/gram_exemplos.h"
#include "tests/closure_goto.h"
#include "tests/conj_itens.h"
#include "tests/action_goto.h"


void printPairToken(std::vector<std::shared_ptr<Symbol>>& tokens,
                    std::vector<std::string>& values)
{
    for (int i = 0; i < (int)tokens.size(); i++){
        Terminal tt = dynamic_cast<Terminal&>(*tokens[i]);
        std::cout << "(" << tt << ", ";
        std::cout << values[i] << ")" << std::endl;
    }
}

int main(int argc, char* argv[]){
    // Carrega a gramática
    // Gramatica G;        // TODO
    // criaGramaticaTP2(G);


    // int left = 0;
    // int right = 0;
    // std::string program = "1+1";
    // std::vector<std::shared_ptr<Symbol>> tokens;
    // std::vector<std::string> values;
    // Gramatica g;
    // criaGramaticaTP2(g);
    // TabelaAction t1;
    // TabelaGoto t2;
    // tabActionGoto(t1, t2, g, true);


    // findTokens(program, tokens, values, left, right, false);
    // (parser(tokens,g));


    
    // Inicialização e entrada do usuário
    std::cout << "==========AVALIADOR DE EXPRESSÕES==========" << std::endl;
    std::cout << "Digite a expressão: ";
    // std::string entrada = "1+1,1+1,7E10,cos(10)";
    std::string entrada;
    std::getline(std::cin, entrada);

    bool exprToProcess = true;

    if (entrada == "print"){
        Gramatica G;       
        criaGramaticaTP2(G);
        outputTables(G, "print.txt");
        exprToProcess = false;
    }
    if (entrada == "quit"){
        exit(EXIT_SUCCESS);
    }
    
    int left = 0;
    int right = 0;
    while(exprToProcess){
        Gramatica G;        // TODO
        criaGramaticaTP2(G);
        std::vector<std::shared_ptr<Symbol>> symbols;
        std::vector<std::string> values;
        values.clear();
        symbols.clear();
        exprToProcess = findTokens(entrada, symbols, values, left, right, true);
        printPairToken(symbols, values);
        bool accept = parser(symbols, G); 
        if (!accept){ exit(EXIT_FAILURE); }
        std::cout << std::endl;
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