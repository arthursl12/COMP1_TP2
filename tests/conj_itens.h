#ifndef CONJ_ITENS_H
#define CONJ_ITENS_H

#include "cadeia.h"
#include "symbol.h"
#include "gram.h"

#include <vector>
#include <memory>

void cria_producoes(std::vector<std::shared_ptr<Producao>>& prods){
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
}

void cria_sets_manual(std::set<std::set<std::shared_ptr<Item>>>& out){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();
    cria_producoes(prods);

    // Conjunto I0
    std::shared_ptr<Item> en1 = std::make_shared<Item>(*prods[0]); // S'->.E
    std::shared_ptr<Item> en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    std::shared_ptr<Item> en3 = std::make_shared<Item>(*prods[1],1); // E->.T
    std::shared_ptr<Item> en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    std::shared_ptr<Item> en5 = std::make_shared<Item>(*prods[2],1); // T->.F
    std::shared_ptr<Item> en6 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    std::shared_ptr<Item> en7 = std::make_shared<Item>(*prods[3],1); // F->.id
    std::set<std::shared_ptr<Item>> IT0;
    IT0.insert(en1);
    IT0.insert(en2);
    IT0.insert(en3);
    IT0.insert(en4);
    IT0.insert(en5);
    IT0.insert(en6);
    IT0.insert(en7);

    // Conjunto I1
    en1 = std::make_shared<Item>(*prods[0]); // S'->.E
    en1->avanca(); // S'->E.
    en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    en2->avanca(); // E->E.+T
    std::set<std::shared_ptr<Item>> IT1;
    IT1.insert(en1);
    IT1.insert(en2);

    // Conjunto I2
    en3 = std::make_shared<Item>(*prods[1],1); // E->.T
    en3->avanca();  // E->T.
    en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    en4->avanca();  // T->T.*F
    std::set<std::shared_ptr<Item>> IT2;
    IT2.insert(en3);
    IT2.insert(en4);

    // Conjunto I3
    en5 = std::make_shared<Item>(*prods[2],1); // T->.F
    en5->avanca();  // T->F.
    std::set<std::shared_ptr<Item>> IT3;
    IT3.insert(en5);

    // Conjunto I4
    en6 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    en6->avanca();  // F->(.E)
    en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    en3 = std::make_shared<Item>(*prods[1],1); // E->.T
    en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    en5 = std::make_shared<Item>(*prods[2],1); // T->.F
    en7 = std::make_shared<Item>(*prods[3],1); // F->.id
    std::shared_ptr<Item> en8 = std::make_shared<Item>(*prods[3]);  // F->.(E)
    std::set<std::shared_ptr<Item>> IT4;
    IT4.insert(en6);
    IT4.insert(en2);
    IT4.insert(en3);
    IT4.insert(en4);
    IT4.insert(en5);
    IT4.insert(en7);
    IT4.insert(en7);
    IT4.insert(en8);


    // Conjunto I5
    en7 = std::make_shared<Item>(*prods[3],1); // F->.id
    en7->avanca(); // F->id.
    std::set<std::shared_ptr<Item>> IT5;
    IT5.insert(en7);
    
    // Conjunto I6
    en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    en2->avanca(); // E->E.+T
    en2->avanca(); // E->E+.T
    en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    en5 = std::make_shared<Item>(*prods[2],1); // T->.F
    en6 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    en7 = std::make_shared<Item>(*prods[3],1); // F->.id
    std::set<std::shared_ptr<Item>> IT6;
    IT6.insert(en2);
    IT6.insert(en4);
    IT6.insert(en5);
    IT6.insert(en6);
    IT6.insert(en7);

    // Conjunto I7
    en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    en4->avanca(); // T->T.*F
    en4->avanca(); // T->T*.F
    en6 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    en7 = std::make_shared<Item>(*prods[3],1); // F->.id
    std::set<std::shared_ptr<Item>> IT7;
    IT7.insert(en4);
    IT7.insert(en6);
    IT7.insert(en7);

    // Conjunto I8
    en6 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    en6->avanca(); // F->(.E)
    en6->avanca(); // F->(E.)
    en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    en2->avanca(); // E->E.+T
    std::set<std::shared_ptr<Item>> IT8;
    IT8.insert(en2);
    IT8.insert(en6);

    // Conjunto I9
    en2 = std::make_shared<Item>(*prods[1]); // E->.E+T
    en2->avanca(); // E->E.+T
    en2->avanca(); // E->E+.T
    en2->avanca(); // E->E+T.
    en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    en4->avanca(); // T->T.*F
    std::set<std::shared_ptr<Item>> IT9;
    IT9.insert(en2);
    IT9.insert(en4);

    // Conjunto I10
    en4 = std::make_shared<Item>(*prods[2]);   // T->.T*F
    en4->avanca(); // T->T.*F
    en4->avanca(); // T->T*.F
    en4->avanca(); // T->T*F.
    std::set<std::shared_ptr<Item>> IT10;
    IT10.insert(en4);

    // Conjunto I1
    en6 = std::make_shared<Item>(*prods[3]);   // F->.(E)
    en6->avanca(); // F->(.E)
    en6->avanca(); // F->(E.)
    en6->avanca(); // F->(E).
    std::set<std::shared_ptr<Item>> IT11;
    IT11.insert(en6);

    out.insert(IT0);
    out.insert(IT1);
    out.insert(IT2);
    out.insert(IT3);
    out.insert(IT4);
    out.insert(IT5);
    out.insert(IT6);
    out.insert(IT7);
    out.insert(IT8);
    out.insert(IT9);
    out.insert(IT10);
    out.insert(IT11);
}

#endif /* CONJ_ITENS_H */
