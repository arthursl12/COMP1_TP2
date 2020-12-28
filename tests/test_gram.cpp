#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cadeia.h"
#include "prod.h"
#include "gram.h"
#include "gram_exemplos.h"

#include <vector>
#include <memory>
#include <set>

void producoes(std::vector<std::shared_ptr<Producao>>& prods){
    prods.clear();

    // E' -> E
    std::vector<std::shared_ptr<Cadeia>> v;
    std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("E");
    v.push_back(std::make_shared<Cadeia>(sym));
    std::shared_ptr<Producao> p = \
        std::make_shared<Producao>(NaoTerminal("E\'"), v);
    prods.push_back(p);

    // E -> E+T | T
    v.clear();
    std::vector<std::shared_ptr<Symbol>> cad;
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    cad.push_back(std::make_shared<Terminal>("+"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<NaoTerminal>("T");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("E"), v);
    prods.push_back(p);

    // T -> T*F | F
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<Terminal>("*"));
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<NaoTerminal>("F");
    v.push_back(std::make_shared<Cadeia>(sym));
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

TEST_CASE("Gramática: construção"){
    std::vector<std::shared_ptr<Producao>> prods;
    producoes(prods);
    CHECK_NOTHROW(Gramatica prods );
    CHECK_NOTHROW(Gramatica());
}

TEST_CASE("Gramática: print"){
    std::vector<std::shared_ptr<Producao>> prods;
    producoes(prods);
    CHECK_NOTHROW(std::cout << Gramatica(prods) << std::endl);
    CHECK_NOTHROW(std::cout << Gramatica() << std::endl);
}

TEST_CASE("Gramática: conjunto terminais"){
    std::vector<std::shared_ptr<Producao>> prods;
    producoes(prods);
    Gramatica g = Gramatica(prods);

    std::set<Terminal> conj_terminais;
    conj_terminais.insert(Terminal("+"));
    conj_terminais.insert(Terminal("("));
    conj_terminais.insert(Terminal("*"));
    conj_terminais.insert(Terminal(")"));
    conj_terminais.insert(Terminal("id"));

    std::set<Terminal> out;
    g.conjuntoTerminais(out);

    CHECK(out == conj_terminais);
}

TEST_CASE("Gramática: conjunto não-terminais"){
    std::vector<std::shared_ptr<Producao>> prods;
    producoes(prods);
    Gramatica g = Gramatica(prods);

    std::set<NaoTerminal> conj_n_terminais;
    conj_n_terminais.insert(NaoTerminal("E\'"));
    conj_n_terminais.insert(NaoTerminal("E"));
    conj_n_terminais.insert(NaoTerminal("T"));
    conj_n_terminais.insert(NaoTerminal("F"));

    std::set<NaoTerminal> out;
    g.conjuntoNaoTerminais(out);
    CHECK(out == conj_n_terminais);
}

TEST_CASE("Gramática: integridade não-terminais"){
    std::vector<std::shared_ptr<Producao>> prods;
    std::vector<std::shared_ptr<Cadeia>> v;
    std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("E");
    v.push_back(std::make_shared<Cadeia>(sym));
    std::shared_ptr<Producao> p = \
        std::make_shared<Producao>(NaoTerminal("E\'"), v);
    prods.push_back(p);

    CHECK_THROWS(Gramatica(prods));
}

TEST_CASE("Gramática: getInicial"){
    SUBCASE("Gramática Genérica"){
        Gramatica g;
        cria_gram_1(g);

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

        CHECK(g.getInicial() == *p);
    }
    SUBCASE("Gramática Default"){
        Gramatica g;

        std::vector<std::shared_ptr<Cadeia>> v;
        std::shared_ptr<Producao> p;

        // E -> TE'
        v.clear();
        v.push_back(std::make_shared<Cadeia>());
        p = std::make_shared<Producao>(NaoTerminal("S"), v);

        CHECK(g.getInicial() == *p);
    }
    
}


TEST_CASE("Gramática: qtdCadeias"){
    SUBCASE("Gramática \"vazia\""){
        Gramatica g;
        std::shared_ptr<NaoTerminal> sym = std::make_shared<NaoTerminal>("S");
        CHECK(g.qtdCadeias(sym) == 1);
    }
    SUBCASE("Gramática Genérica"){
        Gramatica g;
        cria_gram_1(g);
        std::shared_ptr<NaoTerminal> sym;
        
        sym = std::make_shared<NaoTerminal>("E");
        CHECK(g.qtdCadeias(sym) == 1);

        sym = std::make_shared<NaoTerminal>("E\'");
        CHECK(g.qtdCadeias(sym) == 2);

        sym = std::make_shared<NaoTerminal>("T");
        CHECK(g.qtdCadeias(sym) == 1);

        sym = std::make_shared<NaoTerminal>("T\'");
        CHECK(g.qtdCadeias(sym) == 2);

        sym = std::make_shared<NaoTerminal>("F");
        CHECK(g.qtdCadeias(sym) == 2);

        sym = std::make_shared<NaoTerminal>("Z1");
        CHECK(g.qtdCadeias(sym) == 0);
    }
    SUBCASE("Gramática Genérica 2"){
        Gramatica g;
        cria_gram_2(g);
        std::shared_ptr<NaoTerminal> sym;
        
        sym = std::make_shared<NaoTerminal>("S");
        CHECK(g.qtdCadeias(sym) == 3);

        sym = std::make_shared<NaoTerminal>("A");
        CHECK(g.qtdCadeias(sym) == 2);

        sym = std::make_shared<NaoTerminal>("B");
        CHECK(g.qtdCadeias(sym) == 2);

        sym = std::make_shared<NaoTerminal>("C");
        CHECK(g.qtdCadeias(sym) == 2);

        sym = std::make_shared<NaoTerminal>("Z");
        CHECK(g.qtdCadeias(sym) == 0);
    }
    
}