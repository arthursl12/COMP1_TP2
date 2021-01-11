#include <iostream>
#include <string>

#include "lex.h"
#include "conj.h"
#include "gram.h"
#include "tp.h"
#include "utils.h"
#include "tabelas.h"
#include "parser.h"

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
    
    // Inicialização e entrada do usuário
    std::cout << "==========AVALIADOR DE EXPRESSÕES==========" << std::endl;
    std::cout << "Digite a expressão: ";
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
        Gramatica G;  
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
    
    return 0;
    
}