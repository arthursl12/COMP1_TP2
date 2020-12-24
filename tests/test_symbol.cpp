#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "symbol.h"

TEST_CASE("symbol: não instancia"){
    CHECK_THROWS(Symbol());
}

TEST_CASE("Terminal: construção"){
    SUBCASE("Normais"){
        CHECK_NOTHROW(Terminal("a"));
        CHECK_NOTHROW(Terminal("1"));
    }
    SUBCASE("Especiais"){
        CHECK_NOTHROW(Terminal(""));
        CHECK_NOTHROW(Terminal("$"));
        CHECK_NOTHROW(Terminal("."));
        CHECK_NOTHROW(Terminal(","));
    }
    SUBCASE("Inválidos"){
        CHECK_THROWS(Terminal("12"));
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
    }
}