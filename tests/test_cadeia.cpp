#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "symbol.h"
#include "cadeia.h"
#include "doctest.h"

#include <vector>
#include <memory>

TEST_CASE("Cadeia: construção"){
    SUBCASE("Construtor Simples"){
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        CHECK_NOTHROW(Cadeia(p1));
    }
    SUBCASE("Construir via vetor"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        CHECK_NOTHROW(Cadeia(v1));
    }
    SUBCASE("Construtor default"){
        CHECK_NOTHROW(Cadeia());
    }
}

TEST_CASE("Cadeia: operador []"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        Cadeia c = Cadeia(v1);

        CHECK(c[0] == Terminal("a"));
        CHECK(c[1] == Terminal("b"));
        CHECK(c[5] == NaoTerminal("B1"));
        CHECK_THROWS(c[10]);
}

TEST_CASE("Cadeia: operador comparação igualdade"){
        SUBCASE("Qtd elementos"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("b"));
            Cadeia c2 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c3 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
            CHECK_FALSE(c1 == c3);
        }
        SUBCASE("Tipo dos elementos"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<NaoTerminal>("a"));
            v1.push_back(std::make_shared<NaoTerminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c2 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
        }
        SUBCASE("Teste simples"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c2 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c3 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
            CHECK(c1 == c3);
        }
}

TEST_CASE("Print"){
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    CHECK_NOTHROW(std::cout << Cadeia(p1) << std::endl);

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    CHECK_NOTHROW(std::cout << Cadeia(v1) << std::endl);

    CHECK_NOTHROW(std::cout << Cadeia() << std::endl);
}

