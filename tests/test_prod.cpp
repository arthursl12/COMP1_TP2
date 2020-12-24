#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "symbol.h"
#include "prod.h"
#include "doctest.h"

#include <vector>

TEST_CASE("Cadeia: construção"){
    SUBCASE("Construtor Simples"){
        CHECK_NOTHROW(Cadeia(Terminal("")));
        CHECK_THROWS(Cadeia());
    }
    SUBCASE("Construir via vetor"){
        std::vector<Symbol> v1;
        v1.push_back(Terminal("a"));
        v1.push_back(Terminal("b"));
        v1.push_back(NaoTerminal("B1"));
        v1.push_back(Terminal("b"));
        v1.push_back(NaoTerminal("B1"));
        v1.push_back(NaoTerminal("B1"));
        CHECK_NOTHROW(Cadeia(v1));
    }
}

TEST_CASE("Cadeia: operador []"){
        std::vector<Symbol> v1;
        v1.push_back(Terminal("a"));
        v1.push_back(Terminal("b"));
        v1.push_back(NaoTerminal("B1"));
        v1.push_back(Terminal("b"));
        v1.push_back(NaoTerminal("B1"));
        v1.push_back(NaoTerminal("B1"));
        Cadeia c = Cadeia(v1);

        CHECK(c[0] == Terminal("a"));
        CHECK(c[1] == Terminal("b"));
        CHECK(c[5] == NaoTerminal("B1"));
        CHECK_THROWS(c[6]);
}