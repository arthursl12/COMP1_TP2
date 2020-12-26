#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cadeia.h"
#include "prod.h"
#include "doctest.h"
#include <vector>

TEST_CASE("Produção: construção"){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    CHECK_NOTHROW(Producao(NaoTerminal("B1"),prods));
    CHECK_NOTHROW(Producao());
}

TEST_CASE("Produção: setInicial/isInicial"){
    SUBCASE("Construtor Default"){
        Producao p = Producao();
        CHECK(p.isInicial() == false);
        p.setInicial();
        CHECK(p.isInicial() == true);
    }
    SUBCASE("Geral"){
        std::vector<std::shared_ptr<Cadeia>> prods;
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        prods.push_back(std::make_shared<Cadeia>(p1));
        p1 = std::make_shared<Terminal>("a");
        prods.push_back(std::make_shared<Cadeia>(p1));

        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        prods.push_back(std::make_shared<Cadeia>(v1));

        Producao p = Producao(NaoTerminal("B1"),prods);
        CHECK(p.isInicial() == false);
        p.setInicial();
        CHECK(p.isInicial() == true);
    }
}

TEST_CASE("Produção: removeInicial"){
    SUBCASE("Construtor Default"){
        Producao p = Producao();
        p.setInicial();
        p.removeInicial();
        CHECK(p.isInicial() == false);
    }
    SUBCASE("Geral"){
        std::vector<std::shared_ptr<Cadeia>> prods;
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        prods.push_back(std::make_shared<Cadeia>(p1));
        p1 = std::make_shared<Terminal>("a");
        prods.push_back(std::make_shared<Cadeia>(p1));

        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        prods.push_back(std::make_shared<Cadeia>(v1));

        Producao p = Producao(NaoTerminal("B1"),prods);
        p.setInicial();
        p.removeInicial();
        CHECK(p.isInicial() == false);
    }
}

TEST_CASE("Produção: qtdCadeias"){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    CHECK(Producao(NaoTerminal("B1"),prods).qtdCadeias() == 3);
    CHECK(Producao().qtdCadeias() == 1);
}

void criaProducao(Producao& out){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    out = Producao(NaoTerminal("B1"),prods);
}

TEST_CASE("Produção: atributos"){
    Producao p;
    criaProducao(p);
    CHECK(p.label() == NaoTerminal("B1"));

}

TEST_CASE("Produção: acesso"){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    Producao p = Producao(NaoTerminal("B1"),prods);

    p1 = std::make_shared<Terminal>("");
    CHECK(p[0] == Cadeia(p1));
    p1 = std::make_shared<Terminal>("a");
    CHECK(p[1] == Cadeia(p1));
    CHECK(p[2] == Cadeia(v1));
    CHECK_THROWS(p[3]);
}

TEST_CASE("Produção: print"){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    CHECK_NOTHROW(std::cout << Producao(NaoTerminal("B1"),prods) << std::endl);

    std::vector<std::shared_ptr<Cadeia>> prods1;
    p1 = std::make_shared<Terminal>("");
    prods1.push_back(std::make_shared<Cadeia>(p1));
    CHECK_NOTHROW(std::cout << Producao(NaoTerminal("E\'"),prods1) << std::endl);
    CHECK_NOTHROW(std::cout << Producao() << std::endl);
}

TEST_CASE("Produção: conjunto terminais"){
    SUBCASE("Geral"){
        // B -> (vazio) | a | abAbBC
        std::vector<std::shared_ptr<Cadeia>> prods;
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        prods.push_back(std::make_shared<Cadeia>(p1));

        p1 = std::make_shared<Terminal>("a");
        prods.push_back(std::make_shared<Cadeia>(p1));

        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("A"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B"));
        v1.push_back(std::make_shared<NaoTerminal>("C"));
        prods.push_back(std::make_shared<Cadeia>(v1));

        Producao p = Producao(NaoTerminal("B"),prods);

        std::set<Terminal> conj_terminais;
        conj_terminais.insert(Terminal("a"));
        conj_terminais.insert(Terminal("b"));

        std::set<Terminal> out;
        p.conjuntoTerminais(out);
        CHECK(out == conj_terminais);
    }
    SUBCASE("Vazio"){
        Producao p = Producao();
        std::set<Terminal> conj_terminais;
        std::set<Terminal> out;
        p.conjuntoTerminais(out);
        CHECK(out == conj_terminais);
        CHECK(out.empty() == true);
        CHECK(conj_terminais.empty());
    }
    
}

TEST_CASE("Produção: conjunto não-terminais"){
    SUBCASE("Geral"){
        // B -> (vazio) | a | abAbBC
        std::vector<std::shared_ptr<Cadeia>> prods;
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        prods.push_back(std::make_shared<Cadeia>(p1));

        p1 = std::make_shared<Terminal>("a");
        prods.push_back(std::make_shared<Cadeia>(p1));

        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("A"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B"));
        v1.push_back(std::make_shared<NaoTerminal>("C"));
        prods.push_back(std::make_shared<Cadeia>(v1));

        Producao p = Producao(NaoTerminal("B"),prods);
        
        std::set<NaoTerminal> conj_n_terminais;
        conj_n_terminais.insert(NaoTerminal("A"));
        conj_n_terminais.insert(NaoTerminal("B"));
        conj_n_terminais.insert(NaoTerminal("C"));

        std::set<NaoTerminal> out;
        p.conjuntoNaoTerminais(out);
        CHECK(out == conj_n_terminais);
    }
    SUBCASE("Vazio"){
        Producao p = Producao();
        std::set<NaoTerminal> conj_n_terminais;
        std::set<NaoTerminal> out;
        p.conjuntoNaoTerminais(out);
        CHECK(out == conj_n_terminais);
        CHECK(out.empty() == true);
        CHECK(conj_n_terminais.empty());
    }
}



