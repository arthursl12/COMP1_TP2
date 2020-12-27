#include <iostream>
#include <string>

#include "lex.h"
#include "gram.h"
#include "tests/gram_exemplos.h"

int main(int argc, char* argv[]){
    Gramatica g;
    cria_gram_1(g);
    gramaticaEstendida(g);

    std::set<std::shared_ptr<Item>> conjI0;
    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> .E
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
    std::shared_ptr<Item> it0 = std::make_shared<Item>(*p); 
    conjI0.insert(it0);

    closure(conjI0, g);
    std::set<std::shared_ptr<Item>> out;
    cria_closure_manual(out);
    out.insert(it0);
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