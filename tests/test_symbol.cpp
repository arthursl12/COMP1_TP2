#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "symbol.h"
#include <memory>

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

TEST_CASE("Symbol: print"){
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

TEST_CASE("Symbol: copy-constructor"){
    SUBCASE("Terminal"){
        Terminal t1 = Terminal("t");
        std::shared_ptr<Terminal> ptr1 = std::make_shared<Terminal>(t1);
        *ptr1 = Terminal("s");

        CHECK(t1 == Terminal("t"));
        CHECK(*ptr1 == Terminal("s"));
        CHECK_FALSE(*ptr1 == t1);

        std::shared_ptr<Terminal> ptr = std::make_shared<Terminal>("id");
        std::shared_ptr<Terminal> ptr2 = std::make_shared<Terminal>(*ptr);
        *ptr = Terminal("z");

        CHECK(*ptr2 == Terminal("id"));
        CHECK_FALSE(*ptr == Terminal("id"));

    }
    SUBCASE("Não-terminal"){
        std::shared_ptr<NaoTerminal> ptr = std::make_shared<NaoTerminal>("id");
        NaoTerminal t1 = NaoTerminal("t");

        std::shared_ptr<NaoTerminal> ptr1 = std::make_shared<NaoTerminal>(t1);
        *ptr1 = NaoTerminal("s");
        CHECK_FALSE(*ptr1 == t1);

        std::shared_ptr<NaoTerminal> ptr2 = std::make_shared<NaoTerminal>(*ptr);
        *ptr = NaoTerminal("z");
        CHECK_FALSE(*ptr == NaoTerminal("id"));
    }
}
TEST_CASE("Nao-Terminal: labelsize"){
    CHECK(NaoTerminal("a").labelSize() == 1);
    CHECK(NaoTerminal("a1").labelSize() == 2);
    CHECK(NaoTerminal("B").labelSize() == 1);
    CHECK(NaoTerminal("B1").labelSize() == 2);
    CHECK(NaoTerminal("expresao").labelSize() == 8);
}