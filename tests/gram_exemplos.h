#ifndef GRAM_EXEMPLOS_H
#define GRAM_EXEMPLOS_H

#include "cadeia.h"
#include "symbol.h"
#include "gram.h"

#include <vector>
#include <memory>

void cria_gram_0(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // E -> E+T | T
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    cad.push_back(std::make_shared<Terminal>("+"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("E"), v);
    prods.push_back(p);

    // T -> T*F | F
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<Terminal>("*"));
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("T"), v);
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

void cria_gram_1(Gramatica& gram){
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

void cria_gram_2(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> ACB | Cbb | Ba
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    v.push_back(std::make_shared<Cadeia>(cad));

    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    cad.push_back(std::make_shared<Terminal>("b"));
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));

    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<Terminal>("a"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> da | BC
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("d"));
    cad.push_back(std::make_shared<Terminal>("a"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    // B -> g | (vazio)
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("g");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("B"), v);
    prods.push_back(p);

    // C -> h | (vazio)
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("h");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("C"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

void cria_gram_3(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> Aa | Ac
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<Terminal>("a"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<Terminal>("c"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);
    
    // A -> b
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("b");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

void cria_gram_4(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> aBDh
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<NaoTerminal>("D"));
    cad.push_back(std::make_shared<Terminal>("h"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // B -> cC
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("c"));
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("B"), v);
    prods.push_back(p);

    // C -> bC | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("b"));
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("C"), v);
    prods.push_back(p);

    // D -> EF
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("D"), v);
    prods.push_back(p);

    // E -> g | (vazio)
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("g");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("E"), v);
    prods.push_back(p);

    // F -> f | (vazio)
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("f");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("F"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

void cria_gram_5(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> A
    v.clear();
    cad.clear();
    sym = std::make_shared<NaoTerminal>("A");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> aBA'
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<NaoTerminal>("A\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    // A' -> dA' | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("d"));
    cad.push_back(std::make_shared<NaoTerminal>("A\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("A\'"), v);
    prods.push_back(p);

    // B -> b
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("b");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("B"), v);
    prods.push_back(p);

    // C -> g
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("g");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("C"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

void cria_gram_6(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> (L) | a
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("("));
    cad.push_back(std::make_shared<NaoTerminal>("L"));
    cad.push_back(std::make_shared<Terminal>(")"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("a");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // L -> SL'
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("S"));
    cad.push_back(std::make_shared<NaoTerminal>("L\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("L"), v);
    prods.push_back(p);

    // L' -> ,SL' | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>(","));
    cad.push_back(std::make_shared<NaoTerminal>("S"));
    cad.push_back(std::make_shared<NaoTerminal>("L\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("L\'"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

void cria_gram_7(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> AaAb | BbBa
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<Terminal>("b"));
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<Terminal>("a"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> (vazio)
    v.clear();
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    
    // B -> (vazio)
    v.clear();
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("B"), v);
    prods.push_back(p);
    
    gram = Gramatica(prods);
}



#endif // GRAM_EXEMPLOS_H
