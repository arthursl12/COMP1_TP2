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
    // S_EXPR -> T | SIGN T | S_EXPR MULOP FA
    // T -> FA | T MULOP FA
    // FA -> id | constant | ( EXPR ) | FR | NOT FA
    // FR -> SPECOP ( S_EXPR )
    // SIGN -> + | -


    // EXPR_LS -> EXPR | EXPR_LS , EXPR
    v.clear();
    sym = std::make_shared<NaoTerminal>("EXPR");
    v.push_back(std::make_shared<Cadeia>(sym));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("EXPR_LS"));
    cad.push_back(std::make_shared<Terminal>(","));
    cad.push_back(std::make_shared<NaoTerminal>("EXPR"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("EXPR_LS"), v);
    prods.push_back(p);

    // EXPR -> S_EXPR | S_EXPR RELOP S_EXPR
    v.clear();
    sym = std::make_shared<NaoTerminal>("S_EXPR");
    v.push_back(std::make_shared<Cadeia>(sym));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("S_EXPR"));
    cad.push_back(std::make_shared<Terminal>("RELOP"));
    cad.push_back(std::make_shared<NaoTerminal>("S_EXPR"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("EXPR"), v);
    prods.push_back(p);

    // S_EXPR -> T | SIGN T | S_EXPR ADDOP T
    v.clear();
    sym = std::make_shared<NaoTerminal>("T");
    v.push_back(std::make_shared<Cadeia>(sym));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("SIGN"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("S_EXPR"));
    cad.push_back(std::make_shared<Terminal>("ADDOP"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S_EXPR"), v);
    prods.push_back(p);

    // T -> FA | T MULOP FA
    v.clear();
    sym = std::make_shared<NaoTerminal>("FA");
    v.push_back(std::make_shared<Cadeia>(sym));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<Terminal>("MULOP"));
    cad.push_back(std::make_shared<NaoTerminal>("FA"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("T"), v);
    prods.push_back(p);

    // FA -> id | constant | ( EXPR ) | FR | NOT FA
    v.clear();
    sym = std::make_shared<Terminal>("id");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("constant");
    v.push_back(std::make_shared<Cadeia>(sym));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("("));
    cad.push_back(std::make_shared<NaoTerminal>("EXPR"));
    cad.push_back(std::make_shared<Terminal>(")"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<NaoTerminal>("FR");
    v.push_back(std::make_shared<Cadeia>(sym));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("NOT"));
    cad.push_back(std::make_shared<NaoTerminal>("FA"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("FA"), v);
    prods.push_back(p);

    // FR -> SPECOP ( S_EXPR )
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("SPECOP"));
    cad.push_back(std::make_shared<Terminal>("("));
    cad.push_back(std::make_shared<NaoTerminal>("S_EXPR"));
    cad.push_back(std::make_shared<Terminal>(")"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("FR"), v);
    prods.push_back(p);

    // SIGN -> + | -
    v.clear();
    sym = std::make_shared<Terminal>("+");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("-");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("SIGN"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

#endif /* TP */