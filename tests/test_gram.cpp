#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cadeia.h"
#include "prod.h"
#include "gram.h"
#include "item.h"
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

TEST_CASE("Gramática: getProdIndex"){
    SUBCASE("Gramática Default"){
        Gramatica g;
        Cadeia cad = Cadeia();
        CHECK(g.getProdIndex(NaoTerminal("S"),cad) == 0);
        
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("a");
        cad = Cadeia(sym);

        CHECK(g.getProdIndex(NaoTerminal("S"),cad) == -1);
        CHECK(g.getProdIndex(NaoTerminal("T"),cad) == -1);
    }
    SUBCASE("Gramática Genérica"){
        Gramatica g;
        cria_gram_1(g);
    
        std::vector<std::shared_ptr<Symbol>> cad;
        std::shared_ptr<Symbol> sym;        
        Cadeia c;

        // E -> TE'
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("T"));
        cad.push_back(std::make_shared<NaoTerminal>("E\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("E"),c) == 0);

        // E' -> +TE' | (vazio)
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("+"));
        cad.push_back(std::make_shared<NaoTerminal>("T"));
        cad.push_back(std::make_shared<NaoTerminal>("E\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("E\'"),c) == 1);

        sym = std::make_shared<Terminal>("");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("E\'"),c) == 2);

        // T -> FT'
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("F"));
        cad.push_back(std::make_shared<NaoTerminal>("T\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("T"),c) == 3);

        // T' -> *FT' | (vazio)
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("*"));
        cad.push_back(std::make_shared<NaoTerminal>("F"));
        cad.push_back(std::make_shared<NaoTerminal>("T\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("T\'"),c) == 4);
        
        sym = std::make_shared<Terminal>("");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("T\'"),c) == 5);

        // F -> (E) | id
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("("));
        cad.push_back(std::make_shared<NaoTerminal>("E"));
        cad.push_back(std::make_shared<Terminal>(")"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("F"),c) == 6);

        sym = std::make_shared<Terminal>("id");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("F"),c) == 7);
    }
    SUBCASE("Gramática Genérica 2"){
        Gramatica g;
        cria_gram_2(g);

        std::vector<std::shared_ptr<Symbol>> cad;
        std::shared_ptr<Symbol> sym;        
        Cadeia c;

        // S -> ACB | Cbb | Ba
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("A"));
        cad.push_back(std::make_shared<NaoTerminal>("C"));
        cad.push_back(std::make_shared<NaoTerminal>("B"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("S"),c) == 0);

        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("C"));
        cad.push_back(std::make_shared<Terminal>("b"));
        cad.push_back(std::make_shared<Terminal>("b"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("S"),c) == 1);

        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("B"));
        cad.push_back(std::make_shared<Terminal>("a"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("S"),c) == 2);

        // A -> da | BC
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("d"));
        cad.push_back(std::make_shared<Terminal>("a"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("A"),c) == 3);
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("B"));
        cad.push_back(std::make_shared<NaoTerminal>("C"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("A"),c) == 4);

        // B -> g | (vazio)
        cad.clear();
        sym = std::make_shared<Terminal>("g");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("B"),c) == 5);
        sym = std::make_shared<Terminal>("");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("B"),c) == 6);

        // C -> h | (vazio)
        cad.clear();
        sym = std::make_shared<Terminal>("h");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("C"),c) == 7);
        sym = std::make_shared<Terminal>("");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("C"),c) == 8);
    }
    SUBCASE("Gramática Aumentada: default"){
        Gramatica g;
        gramaticaEstendida(g);
        Cadeia cad = Cadeia();
        CHECK(g.getProdIndex(NaoTerminal("S"),cad) == 1);
        
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("a");
        cad = Cadeia(sym);

        CHECK(g.getProdIndex(NaoTerminal("S"),cad) == -1);
        CHECK(g.getProdIndex(NaoTerminal("T"),cad) == -1);

        sym = std::make_shared<NaoTerminal>("S");
        cad = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("S\'"),cad) == 0);
    }
    SUBCASE("Gramática Aumentada: genérica"){
        Gramatica g;
        cria_gram_1(g);
        gramaticaEstendida(g);
    
        std::vector<std::shared_ptr<Symbol>> cad;
        std::shared_ptr<Symbol> sym;        
        Cadeia c;

        // E -> TE'
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("T"));
        cad.push_back(std::make_shared<NaoTerminal>("E\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("E"),c) == 1);

        // E' -> +TE' | (vazio)
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("+"));
        cad.push_back(std::make_shared<NaoTerminal>("T"));
        cad.push_back(std::make_shared<NaoTerminal>("E\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("E\'"),c) == 2);

        sym = std::make_shared<Terminal>("");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("E\'"),c) == 3);

        // T -> FT'
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("F"));
        cad.push_back(std::make_shared<NaoTerminal>("T\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("T"),c) == 4);

        // T' -> *FT' | (vazio)
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("*"));
        cad.push_back(std::make_shared<NaoTerminal>("F"));
        cad.push_back(std::make_shared<NaoTerminal>("T\'"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("T\'"),c) == 5);
        
        sym = std::make_shared<Terminal>("");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("T\'"),c) == 6);

        // F -> (E) | id
        cad.clear();
        cad.push_back(std::make_shared<Terminal>("("));
        cad.push_back(std::make_shared<NaoTerminal>("E"));
        cad.push_back(std::make_shared<Terminal>(")"));
        c = Cadeia(cad);
        CHECK(g.getProdIndex(NaoTerminal("F"),c) == 7);

        sym = std::make_shared<Terminal>("id");
        c = Cadeia(sym);
        CHECK(g.getProdIndex(NaoTerminal("F"),c) == 8);
    }
    SUBCASE("Cadeias com ponto"){
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
        Cadeia c = Cadeia(cad);
        p = std::make_shared<Producao>(NaoTerminal("E"), v);

        Item it = Item(*p);
        CHECK(g.getProdIndex(it.label(),it.getCadeia()) == 0);
    }
}