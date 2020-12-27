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

TEST_CASE("Item: integridade do construtor"){
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
        CHECK_FALSE(*cad == it.getCadeia());
        CHECK((*cad)[1] == Terminal("b"));
    }
}

TEST_CASE("Item: cadeia possui ponto"){
    Item it = Item();
    std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
    CHECK(it.getCadeia() == Cadeia(sym));
    sym  = std::make_shared<Terminal>("");
    CHECK_FALSE(it.getCadeia() == Cadeia(sym));

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
    std::shared_ptr<Cadeia> cad = std::make_shared<Cadeia>(v1); 
    prods.push_back(cad);

    Producao p = Producao(NaoTerminal("B1"),prods);
    Item it1 = Item(p);
    CHECK_FALSE(it.getCadeia() == *cad);
}

TEST_CASE("Item: comparador de igualdade"){
    Item it0;
    Item it1 = Item();
    CHECK(it0 == it1);

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
    Item it2 = Item(p);
    Item it3 = Item(p,0);
    Item it4 = Item(p,1);
    Item it5 = Item(p,2);

    CHECK(it3 == it2);
    CHECK_FALSE(it3 == it0);
    CHECK_FALSE(it3 == it4);
    CHECK_FALSE(it3 == it5);

    v1.clear();
    prods.clear();
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    p = Producao(NaoTerminal("B1"),prods);
    Item it6 = Item(p);

    CHECK(it5 == it6);

    v1.clear();
    prods.clear();
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    p = Producao(NaoTerminal("C"),prods);
    Item it7 = Item(p);

    CHECK_FALSE(it5 == it7);

    v1.clear();
    prods.clear();
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("c"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    p = Producao(NaoTerminal("B1"),prods);
    Item it8 = Item(p);

    CHECK_FALSE(it5 == it8);
}

TEST_CASE("Item: avanca"){
    SUBCASE("Item default"){
        Item it = Item();

        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
        CHECK(it.getCadeia() == Cadeia(sym));

        it.avanca();
        CHECK(it.getCadeia() == Cadeia(sym));
    }
    SUBCASE("Geral"){
        std::vector<std::shared_ptr<Cadeia>> prods;
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        prods.push_back(std::make_shared<Cadeia>(p1));
        p1 = std::make_shared<Terminal>("a");
        prods.push_back(std::make_shared<Cadeia>(p1));

        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("id"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        std::shared_ptr<Cadeia> cad = std::make_shared<Cadeia>(v1); 
        prods.push_back(cad);

        Producao p = Producao(NaoTerminal("B1"),prods);
        Item it = Item(p,2);
        v1.clear();
        v1.push_back(std::make_shared<Terminal>("."));
        v1.push_back(std::make_shared<Terminal>("id"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        cad = std::make_shared<Cadeia>(v1);
        CHECK(it.getCadeia() == *cad);

        it.avanca();
        CHECK_FALSE(it.getCadeia() == *cad);
        v1.clear();
        v1.push_back(std::make_shared<Terminal>("id"));
        v1.push_back(std::make_shared<Terminal>("."));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        cad = std::make_shared<Cadeia>(v1);
        CHECK(it.getCadeia() == *cad);

        it.avanca();
        CHECK_FALSE(it.getCadeia() == *cad);
        v1.clear();
        v1.push_back(std::make_shared<Terminal>("id"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<Terminal>("."));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        cad = std::make_shared<Cadeia>(v1);
        CHECK(it.getCadeia() == *cad);

        it.avanca();
        CHECK_FALSE(it.getCadeia() == *cad);
        v1.clear();
        v1.push_back(std::make_shared<Terminal>("id"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("."));
        cad = std::make_shared<Cadeia>(v1);
        CHECK(it.getCadeia() == *cad);

        it.avanca();
        CHECK(it.getCadeia() == *cad);
    }
}

TEST_CASE("Item: copy-constructor"){
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
    std::shared_ptr<Item> it1 = std::make_shared<Item>(it);
    CHECK(it == *it1);
    it1->avanca();
    CHECK_FALSE(it == *it1);
}

