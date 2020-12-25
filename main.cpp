#include <iostream>
#include <string>

#include "lex.h"
#include "gram.h"

void cria_gram(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // E -> TE'
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<NaoTerminal>("E\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("E"), v);
    prods.push_back(p);

    // E' -> +TE' | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("+"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<NaoTerminal>("E\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("E\'"), v);
    prods.push_back(p);

    // T -> FT'
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    cad.push_back(std::make_shared<NaoTerminal>("T\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("T"), v);
    prods.push_back(p);

    // T' -> *FT' | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("*"));
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    cad.push_back(std::make_shared<NaoTerminal>("T\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("T\'"), v);
    prods.push_back(p);

    // F -> (E) | id
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("("));
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    cad.push_back(std::make_shared<Terminal>(")"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("id");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("F"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}


int main(int argc, char* argv[]){
    Gramatica g;
    cria_gram(g);

    // FIRST(F) = {(,id}
    std::set<Terminal> conj_first;
    conj_first.insert(Terminal("("));
    conj_first.insert(Terminal("id"));

    std::set<Terminal> out;
    std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("F");
    g.first(sym, out);
    std::cout << "CONJ: " << std::endl;
    for (auto it = conj_first.begin(); it != conj_first.end(); it++){
        std::cout << "\t" << *it << std::endl;
    }
    std::cout << "OUT: " << std::endl;
    for (auto it = out.begin(); it != out.end(); it++){
        std::cout << "\t" << *it << std::endl;
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