#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "prod.h"
#include "item.h"
#include "doctest.h"

#include <vector>
#include <memory>

TEST_CASE("Item: construção"){
    SUBCASE("Construtor Simples"){
        CHECK_NOTHROW(Item it);
        CHECK_NOTHROW(Item());
    }
    SUBCASE("Construir a partir de produção (ponto default)"){
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
        CHECK_NOTHROW(Item it(p));
    }
    SUBCASE("Construir a partir de produção (ponto especificado)"){
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
        CHECK_NOTHROW(Item it(p,2));
    }
}

TEST_CASE("Item: impressão"){
    SUBCASE("Construtor Simples"){
        CHECK_NOTHROW(std::cout << Item() << std::endl);
    }
    SUBCASE("Construir a partir de produção (ponto default)"){
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
        CHECK_NOTHROW(std::cout << Item(p) << std::endl);
    }
    SUBCASE("Construir a partir de produção (ponto especificado)"){
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
        CHECK_NOTHROW(std::cout << Item(p,2) << std::endl);
    }
}

TEST_CASE("Item: integridade"){
    SUBCASE("Construtor com índice de produção inválido"){
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
        CHECK_THROWS(Item(p,3));
    }
    SUBCASE("Cadeia da produção não é alterada"){
        std::vector<std::shared_ptr<Cadeia>> prods;
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        prods.push_back(std::make_shared<Cadeia>(p1));
        p1 = std::make_shared<Terminal>("a");
        prods.push_back(std::make_shared<Cadeia>(p1));

        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        std::shared_ptr<Terminal> t1 = std::make_shared<Terminal>("b");
        v1.push_back(t1);
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        std::shared_ptr<Cadeia> cad = std::make_shared<Cadeia>(v1);
        prods.push_back(cad);

        Producao p = Producao(NaoTerminal("B1"),prods);
        Item it = Item(p,2);
        *t1 = Terminal("c");
        CHECK(*cad == it.getCadeia());
        CHECK((*cad)[1] == Terminal("b"));
    }
}