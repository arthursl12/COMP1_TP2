#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "symbol.h"

TEST_CASE("Terminal: construção"){
    SUBCASE("Normais"){
        CHECK_NOTHROW(Terminal("a"));
        CHECK_NOTHROW(Terminal("1"));
        CHECK_NOTHROW(Terminal("else"));
        CHECK_NOTHROW(Terminal("id"));
    }
    SUBCASE("Especiais"){
        CHECK_NOTHROW(Terminal(""));
        CHECK_NOTHROW(Terminal("$"));
        CHECK_NOTHROW(Terminal("."));
        CHECK_NOTHROW(Terminal(","));
    }
    SUBCASE("Inválidos"){
        CHECK_THROWS(Terminal(" "));
    }
}

TEST_CASE("Terminal: específicos"){
    CHECK(Terminal("a").vazio() == false);
    CHECK(Terminal("a").fim() == false);

    CHECK(Terminal("").vazio() == true);
    CHECK(Terminal("").fim() == false);

    CHECK(Terminal("$").vazio() == false);
    CHECK(Terminal("$").fim() == true);
}

TEST_CASE("NaoTerminal: construção"){
    SUBCASE("Válidos"){
        CHECK_NOTHROW(NaoTerminal("a"));
        CHECK_NOTHROW(NaoTerminal("a1"));
        CHECK_NOTHROW(NaoTerminal("B"));
        CHECK_NOTHROW(NaoTerminal("B1"));
        CHECK_NOTHROW(NaoTerminal("expresao"));
        
    }
    SUBCASE("Especiais"){
        CHECK_THROWS(NaoTerminal("1"));
        CHECK_THROWS(NaoTerminal(""));
        CHECK_THROWS(NaoTerminal("$"));
        CHECK_THROWS(NaoTerminal("."));
        CHECK_THROWS(NaoTerminal(","));
        CHECK_THROWS(NaoTerminal("12"));
        CHECK_THROWS(NaoTerminal(" "));
        CHECK_THROWS(NaoTerminal(" B1"));
        CHECK_THROWS(NaoTerminal(" B   "));
        CHECK_THROWS(NaoTerminal(" B\t"));
    }
}

TEST_CASE("Symbol: isTerminal"){
    CHECK(Terminal("a").isTerminal() == true);
    CHECK(NaoTerminal("expr").isTerminal() == false);
}

TEST_CASE("Print"){
    CHECK_NOTHROW(std::cout << Terminal("a") << std::endl);
    CHECK_NOTHROW(std::cout << NaoTerminal("EXPR") << std::endl);
}

TEST_CASE("Symbol: Comparador de Igualdade"){
    SUBCASE("Terminais"){
        CHECK(Terminal("") == Terminal(""));
        CHECK(Terminal("$") == Terminal("$"));
        CHECK(Terminal("a") == Terminal("a"));
        CHECK_FALSE(Terminal("") == Terminal("a"));
        CHECK_FALSE(Terminal("$") == Terminal("a"));
    }
    SUBCASE("Não-terminais"){
        CHECK(NaoTerminal("B1") == NaoTerminal("B1"));
        CHECK(NaoTerminal("expr") == NaoTerminal("expr"));
        CHECK(NaoTerminal("A") == NaoTerminal("A"));
        CHECK_FALSE(NaoTerminal("B1") == NaoTerminal("B2"));
        CHECK_FALSE(NaoTerminal("expr") == NaoTerminal("EXPR"));
    }
}

TEST_CASE("Symbol: menor que"){
    CHECK(Terminal("A") < Terminal("a"));
    CHECK(Terminal("a") < Terminal("b"));
    CHECK(NaoTerminal("B") < NaoTerminal("B1"));
    CHECK(Terminal("") < Terminal("a"));
}