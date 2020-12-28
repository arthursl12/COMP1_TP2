#include <iostream>
#include <string>

#include "lex.h"
#include "gram.h"
#include "utils.h"
#include "tests/gram_exemplos.h"

int main(int argc, char* argv[]){
    Gramatica g;
    cria_gram_closure_1(g);
    gramaticaEstendida(g);

    // std::cout << g << std::endl;

    std::set<std::shared_ptr<Item>> conjI0;
    std::set<std::shared_ptr<Item>> out;
    cria_goto_manual_2(conjI0, out);

    std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("a");
    std::set<std::shared_ptr<Item>> conj_goto;
    funcaoGoto(conjI0, sym, g, conj_goto);
    
    std::cout << "CONJI0:" << std::endl;
    for (auto elm0 : conjI0){
        std::cout << "\t" << *elm0 << std::endl;
    }
    std::cout << "OUT:" << std::endl;
    for (auto elm0 : out){
        std::cout << "\t" << *elm0 << std::endl;
        }
    // Gramatica g;
    // cria_gram_4(g);

    // // FOLLOW(B) = FIRST(D) U {h} = {g,f,h}
    // std::set<Terminal> conj_follow;
    // conj_follow.insert(Terminal("g"));
    // conj_follow.insert(Terminal("f"));
    // conj_follow.insert(Terminal("h"));

    // std::set<Terminal> out;
    // std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("B");
    // g.follow(nt, out);


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