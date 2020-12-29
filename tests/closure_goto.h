
#ifndef CLOSURE_GOTO_H
#define CLOSURE_GOTO_H

#include "cadeia.h"
#include "symbol.h"
#include "gram.h"

#include <vector>
#include <memory>

void cria_gram_closure_1(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S -> AA
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> aA | b
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);
    
    gram = Gramatica(prods);
}

void cria_gram_goto(Gramatica& gram){
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

void cria_closure_manual(std::set<std::shared_ptr<Item>>& out){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;
    // S -> .E
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

    std::shared_ptr<Item> it0 = std::make_shared<Item>(*prods[0]); // E->.TE'
    std::shared_ptr<Item> it1 = std::make_shared<Item>(*prods[2]); // T->.FT'
    std::shared_ptr<Item> it2 = std::make_shared<Item>(*prods[4]); // F->.(E)
    std::shared_ptr<Item> it3 = std::make_shared<Item>(*prods[4],1); // F->.id

    out.insert(it0);
    out.insert(it1);
    out.insert(it2);
    out.insert(it3);
}

void cria_closure_manual_1(std::set<std::shared_ptr<Item>>& out){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;
    // S -> .S
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("S"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
    prods.push_back(p);

    // S -> AA
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> aA | b
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    std::shared_ptr<Item> it0 = std::make_shared<Item>(*prods[0]); // S -> .S
    std::shared_ptr<Item> it1 = std::make_shared<Item>(*prods[1]); // S -> .AA
    std::shared_ptr<Item> it2 = std::make_shared<Item>(*prods[2]); // A -> .aA
    std::shared_ptr<Item> it3 = std::make_shared<Item>(*prods[2],1); // A -> .b

    out.insert(it0);
    out.insert(it1);
    out.insert(it2);
    out.insert(it3);
}

void cria_closure_manual_2(std::set<std::shared_ptr<Item>>& out){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;
    // S -> .S

    // S -> AA
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> aA | b
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);


    // S -> A.A
    std::shared_ptr<Item> it0 = std::make_shared<Item>(*prods[0]); 
    it0->avanca();
    std::shared_ptr<Item> it1 = std::make_shared<Item>(*prods[1]); // A -> .aA
    std::shared_ptr<Item> it2 = std::make_shared<Item>(*prods[1],1); // A -> .b

    out.insert(it0);
    out.insert(it1);
    out.insert(it2);
}

void cria_goto_manual(std::set<std::shared_ptr<Item>>& in, std::set<std::shared_ptr<Item>>& out){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // S' -> .E
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
    prods.push_back(p);

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

    std::shared_ptr<Item> en1 = std::make_shared<Item>(*prods[0]); // S'->.E
    en1->avanca(); // S'->E.
    std::shared_ptr<Item> en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    en2->avanca(); // E->E.+T

    in.insert(en1);
    in.insert(en2);
    
    std::shared_ptr<Item> it0 = std::make_shared<Item>(*prods[1]); // E->.E+T
    it0->avanca();  // E->E.+T
    it0->avanca();  // E->E+.T
    std::shared_ptr<Item> it1 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    std::shared_ptr<Item> it2 = std::make_shared<Item>(*prods[2],1); // T->.F
    std::shared_ptr<Item> it3 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    std::shared_ptr<Item> it4 = std::make_shared<Item>(*prods[3],1); // F->.id

    out.insert(it0);
    out.insert(it1);
    out.insert(it2);
    out.insert(it3);
    out.insert(it4);
}

void cria_goto_manual_1(std::set<std::shared_ptr<Item>>& in, 
                        std::set<std::shared_ptr<Item>>& out)
{
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;
    // S -> .S
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("S"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
    prods.push_back(p);

    // S -> AA
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> aA | b
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    std::shared_ptr<Item> en1 = std::make_shared<Item>(*prods[1]); // S -> .AA
    in.insert(en1);

    std::shared_ptr<Item> it1 = std::make_shared<Item>(*prods[1]); // S -> .AA
    it1->avanca(); // S -> A.A
    std::shared_ptr<Item> it2 = std::make_shared<Item>(*prods[2]); // A -> .aA
    std::shared_ptr<Item> it3 = std::make_shared<Item>(*prods[2],1); // A -> .b

    out.insert(it1);
    out.insert(it2);
    out.insert(it3);
}

void cria_goto_manual_2(std::set<std::shared_ptr<Item>>& in, 
                        std::set<std::shared_ptr<Item>>& out)
{
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;
    // S -> .S
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("S"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
    prods.push_back(p);

    // S -> AA
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    // A -> aA | b
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("a"));
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    std::shared_ptr<Item> en1 = std::make_shared<Item>(*prods[2]); // A -> .aA
    in.insert(en1);

    std::shared_ptr<Item> it2 = std::make_shared<Item>(*prods[2]); // A -> .aA
    it2->avanca(); // A -> a.A
    std::shared_ptr<Item> it3 = std::make_shared<Item>(*prods[2]); // A -> .aA
    std::shared_ptr<Item> it4 = std::make_shared<Item>(*prods[2],1); // A -> .b

    out.insert(it2);
    out.insert(it3);
    out.insert(it4);
}


bool conjuntosIguais(std::set<std::shared_ptr<Item>> c1, 
                     std::set<std::shared_ptr<Item>> c2,
                     bool imprime = true)
{
    // Tudo de c1 está em c2
    for (auto elm0 : c1){
        bool possui = false;
        for (auto elm1 : c2){
            if (*elm1 == *elm0){
                possui = true;
            }
        }
        if (!possui && imprime){
            std::cout << *elm0 << std::endl;
        }
        if (possui == false){ return false;}
    }

    // Tudo de c2 está em c1
    for (auto elm0 : c2){
        bool possui = false;
        for (auto elm1 : c1){
            if (*elm1 == *elm0){
                possui = true;
            }
        }
        if (!possui && imprime){
            std::cout << *elm0 << std::endl;
        }
        if (possui == false){ return false;}
    }

    // Eles tem o mesmo tamanho
    if (c2.size() != c1.size()) { return false;}
    return true;
}


#endif /* CLOSURE_GOTO_H */
