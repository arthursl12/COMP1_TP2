#include <iostream>
#include <string>

#include "lex.h"
#include "gram.h"
#include "tests/gram_exemplos.h"


int main(int argc, char* argv[]){
    Gramatica g;
    cria_gram_7(g);

    // FIRST(S) = FIRST(A) U {a} U FIRST(B) U {b} = {a,b}
    std::set<Terminal> conj_first;
    conj_first.insert(Terminal("a"));
    conj_first.insert(Terminal("b"));

    std::set<Terminal> out;
    std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("S");
    g.first(sym, out);

    for(auto it:out){
        std::cout << "\t" << it << std::endl;
    }



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