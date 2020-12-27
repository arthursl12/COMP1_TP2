#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "gram.h"
#include "item.h"

#include <vector>
#include <memory>
#include "gram_exemplos.h"


TEST_CASE("Utils: gramaticaEstendida"){
    Gramatica g1;
    cria_gram_1(g1);

    std::set<Terminal> ts1;
    g1.conjuntoTerminais(ts1);

    std::set<NaoTerminal> nt1;
    g1.conjuntoNaoTerminais(nt1);

    gramaticaEstendida(g1);
    std::set<Terminal> ts2;
    g1.conjuntoTerminais(ts2);

    std::set<NaoTerminal> nt2;
    g1.conjuntoNaoTerminais(nt2);

    CHECK(ts1 == ts2);

    CHECK(nt1 != nt2);
    nt2.erase(NaoTerminal("S\'"));
    CHECK(nt1 == nt2);
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

TEST_CASE("Utils: closure"){
    Gramatica g;
    cria_gram_1(g);
    gramaticaEstendida(g);

    std::set<std::shared_ptr<Item>> conjI0;
    std::set<std::shared_ptr<Item>> out;
    cria_closure_manual(out);

    for (auto elm0 : conjI0){
        bool possui = false;
        for (auto elm1 : out){
            if (*elm1 == *elm0){
                possui = true;
            }
        }
        CHECK(possui == true);
    }
}
