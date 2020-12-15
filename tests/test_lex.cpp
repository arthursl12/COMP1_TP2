#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lex.h"

TEST_CASE("isAddOp"){
    SUBCASE("Verdadeiro"){
        CHECK(isAddOp("+"));
        CHECK(isAddOp("-"));
        CHECK(isAddOp("or"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isAddOp(""));
        CHECK_FALSE(isAddOp(" "));
        CHECK_FALSE(isAddOp("."));
        CHECK_FALSE(isAddOp("a"));
        CHECK_FALSE(isAddOp("o"));
        CHECK_FALSE(isAddOp("OR"));
        CHECK_FALSE(isAddOp("++"));
        CHECK_FALSE(isAddOp("--"));
    }
}

TEST_CASE("isMulOp"){
    SUBCASE("Verdadeiro"){
        CHECK(isMulOp("*"));
        CHECK(isMulOp("/"));
        CHECK(isMulOp("div"));
        CHECK(isMulOp("mod"));
        CHECK(isMulOp("and"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isMulOp(""));
        CHECK_FALSE(isMulOp("."));
        CHECK_FALSE(isMulOp(" "));
        CHECK_FALSE(isMulOp("**"));
        CHECK_FALSE(isMulOp("//"));
        CHECK_FALSE(isMulOp("a"));
        CHECK_FALSE(isMulOp("an"));
        CHECK_FALSE(isMulOp("d"));
        CHECK_FALSE(isMulOp("di"));
        CHECK_FALSE(isMulOp("m"));
        CHECK_FALSE(isMulOp("mo"));
    }
}

TEST_CASE("isSpecOp"){
    SUBCASE("Verdadeiro"){
        CHECK(isSpecOp("sin"));
        CHECK(isSpecOp("cos"));
        CHECK(isSpecOp("log"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isSpecOp(""));
        CHECK_FALSE(isSpecOp("."));
        CHECK_FALSE(isSpecOp(" "));
        CHECK_FALSE(isSpecOp("l"));
        CHECK_FALSE(isSpecOp("lo"));
        CHECK_FALSE(isSpecOp("s"));
        CHECK_FALSE(isSpecOp("si"));
        CHECK_FALSE(isSpecOp("c"));
        CHECK_FALSE(isSpecOp("co"));
        CHECK_FALSE(isSpecOp("sen"));
    }
}

TEST_CASE("isRelOp"){
    SUBCASE("Verdadeiro"){
        CHECK(isRelOp("="));
        CHECK(isRelOp("<"));
        CHECK(isRelOp(">"));
        CHECK(isRelOp("<>"));
        CHECK(isRelOp("<="));
        CHECK(isRelOp(">="));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isRelOp(""));
        CHECK_FALSE(isRelOp("."));
        CHECK_FALSE(isRelOp(" "));
        CHECK_FALSE(isRelOp("<<"));
        CHECK_FALSE(isRelOp(">>"));
        CHECK_FALSE(isRelOp("!="));
        CHECK_FALSE(isRelOp("=="));
        CHECK_FALSE(isRelOp("=<"));
        CHECK_FALSE(isRelOp("=>"));
    }
}

TEST_CASE("isOperator"){
    SUBCASE("Verdadeiro"){
        CHECK(isOperator("+"));
        CHECK(isOperator("*"));
        CHECK(isOperator("sin"));
        CHECK(isOperator("<"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isOperator(""));
        CHECK_FALSE(isOperator("."));
        CHECK_FALSE(isOperator(" "));
    }
}

TEST_CASE("isDelimiter"){
    SUBCASE("Verdadeiro: espaços"){
        CHECK(isDelimiter(" "));
        CHECK(isDelimiter("\n"));
        CHECK(isDelimiter("\t"));
        CHECK(isDelimiter("\r"));
        CHECK(isDelimiter("            "));
    }
    SUBCASE("Verdadeiro: outros"){
        CHECK(isDelimiter("+"));
        CHECK(isDelimiter(","));
        CHECK(isDelimiter("("));
        CHECK(isDelimiter(")"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isDelimiter(""));
        CHECK_FALSE(isDelimiter("."));
        CHECK_FALSE(isDelimiter(";"));
        CHECK_FALSE(isDelimiter("["));
        CHECK_FALSE(isDelimiter("{"));
    }
}

TEST_CASE("isIdentifier"){
    SUBCASE("Verdadeiro"){
        CHECK(isIdentifier("abc"));
        CHECK(isIdentifier("a"));
        CHECK(isIdentifier("ABC"));
        CHECK(isIdentifier("Abc"));
        CHECK(isIdentifier("A1"));
        CHECK(isIdentifier("a1_"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isIdentifier("1a"));
        CHECK_FALSE(isIdentifier(".a"));
        CHECK_FALSE(isIdentifier("_s"));
        CHECK_FALSE(isIdentifier(""));
        CHECK_FALSE(isIdentifier("  a"));
    }
}

TEST_CASE("subString"){
    CHECK(subString("01234",0,2) == "012");
    CHECK(subString("01234",1,2) == "12");
    CHECK(subString("01234",2,2) == "2");
}

