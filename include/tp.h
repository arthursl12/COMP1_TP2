#ifndef TP_H
#define TP_H

#include "gram.h"
/*
TOKENS:
RELOP, ADDOP, MULOP, SPECOP, identifier, constant, NOT

N-Ts: 
EXPR_LS, EXPR, S_EXPR, T, FA, FR, SIGN

T-s:
(, ), ,, +, - 
*/
void criaGramaticaTP2(Gramatica& gram){
std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    
    // S' -> EXPR_LS
    // EXPR_LS -> EXPR | EXPR_LS , EXPR
    // EXPR -> S_EXPR | S_EXPR RELOP S_EXPR
    // S_EXPR -> T | S T | S_EXPR MULOP F
    // T -> FA | T m FA
    // FA -> id | constant | ( EXPR ) | FR | NOT F
    // FR -> idf | idf ( EXPR_LS )
    // S -> + | -


    // EXPR_LS -> EXPR | EXPR_LS , EXPR

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

#endif /* TP */