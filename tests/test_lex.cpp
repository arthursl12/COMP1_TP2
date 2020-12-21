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

TEST_CASE("isUnsignedInteger"){
    SUBCASE("Verdadeiro"){
        CHECK(isUnsignedInteger("0"));
        CHECK(isUnsignedInteger("12"));
        CHECK(isUnsignedInteger("000002"));
        CHECK(isUnsignedInteger("2000"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isUnsignedInteger("1a"));
        CHECK_FALSE(isUnsignedInteger(".a"));
        CHECK_FALSE(isUnsignedInteger("_s"));
        CHECK_FALSE(isUnsignedInteger(""));
        CHECK_FALSE(isUnsignedInteger("  a"));
        CHECK_FALSE(isUnsignedInteger("0000a"));
        CHECK_FALSE(isUnsignedInteger("-100"));
        CHECK_FALSE(isUnsignedInteger("10.01"));
        CHECK_FALSE(isUnsignedInteger("123E8"));
    }
}

TEST_CASE("isUnsignedReal"){
    SUBCASE("Verdadeiro: inteiros"){
        CHECK(isUnsignedReal("0"));
        CHECK(isUnsignedReal("12"));
        CHECK(isUnsignedReal("000002"));
        CHECK(isUnsignedReal("2000"));
        CHECK(isUnsignedReal("000002"));
        CHECK(isUnsignedReal("2000"));
    }
    SUBCASE("Verdadeiro: decimais"){
        CHECK(isUnsignedReal("12.00001"));
        CHECK(isUnsignedReal("0.0000000"));
        CHECK(isUnsignedReal("0.0000001"));
        CHECK(isUnsignedReal("0.0000000"));

        // Sem parte decimal, mas com ponto
        CHECK(isUnsignedReal("0."));
        CHECK(isUnsignedReal("12."));
        CHECK(isUnsignedReal("1233456."));
    }
    SUBCASE("Verdadeiro: inteiro + expoente"){
        CHECK(isUnsignedReal("0E1"));
        CHECK(isUnsignedReal("00000E1"));
        CHECK(isUnsignedReal("0E-1"));
        CHECK(isUnsignedReal("00000E-1"));
        CHECK(isUnsignedReal("123E-3"));
        CHECK(isUnsignedReal("123E3"));
        CHECK(isUnsignedReal("123E+3"));
    }
    SUBCASE("Verdadeiro: real completo"){
        CHECK(isUnsignedReal("0.E1"));
        CHECK(isUnsignedReal("0.0E-1"));
        CHECK(isUnsignedReal("0000.0000E-11"));
        CHECK(isUnsignedReal("12.00001E+12"));
        CHECK(isUnsignedReal("12.00001E12"));
        CHECK(isUnsignedReal("12.00001E-12"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isUnsignedReal("1a"));
        CHECK_FALSE(isUnsignedReal("_s"));
        CHECK_FALSE(isUnsignedReal(""));
        CHECK_FALSE(isUnsignedReal("  a"));
        CHECK_FALSE(isUnsignedReal("0000a"));

        // Sem parte inteira
        CHECK_FALSE(isUnsignedReal(".a"));
        CHECK_FALSE(isUnsignedReal(".0001"));
        CHECK_FALSE(isUnsignedReal(".001E1"));

        // Expoente Decimal
        CHECK_FALSE(isUnsignedReal("1.001E1.001"));
        CHECK_FALSE(isUnsignedReal("1.001E+1.00"));
        CHECK_FALSE(isUnsignedReal("1.001E-1.001"));
        CHECK_FALSE(isUnsignedReal("1.001E1."));

        // Espaços indevidos
        CHECK_FALSE(isUnsignedReal("1.1E 1"));
        CHECK_FALSE(isUnsignedReal("1.1 E1"));
        CHECK_FALSE(isUnsignedReal("1.1E 1"));
        CHECK_FALSE(isUnsignedReal("1. 1E1"));
        CHECK_FALSE(isUnsignedReal("1 .1E1"));
    }
}

TEST_CASE("isConstant"){
    // Vamos assumir que um real e um inteiro sem sinal são sempre corretamente
    // identificados
    SUBCASE("Verdadeiro: sem sinal"){
        CHECK(isConstant("0"));
        CHECK(isConstant("1"));
        CHECK(isConstant("861654"));
        CHECK(isConstant("1E1"));
        CHECK(isConstant("1E+1"));
        CHECK(isConstant("20.0E-2"));
        CHECK(isConstant("123.001"));
    }
    SUBCASE("Verdadeiro: com sinal"){
        CHECK(isConstant("+0"));
        CHECK(isConstant("+1"));
        CHECK(isConstant("+861654"));
        CHECK(isConstant("+1E1"));
        CHECK(isConstant("+1E+1"));
        CHECK(isConstant("+20.0E-2"));
        CHECK(isConstant("+123.001"));
        CHECK(isConstant("-0"));
        CHECK(isConstant("-1"));
        CHECK(isConstant("-861654"));
        CHECK(isConstant("-1E1"));
        CHECK(isConstant("-1E+1"));
        CHECK(isConstant("-20.0E-2"));
        CHECK(isConstant("-123.001"));
    }
    SUBCASE("Falso"){
        CHECK_FALSE(isConstant("1a"));
        CHECK_FALSE(isConstant("_s"));
        CHECK_FALSE(isConstant(""));
        CHECK_FALSE(isConstant("  a"));
        CHECK_FALSE(isConstant("0000a"));

        // Sem parte inteira
        CHECK_FALSE(isConstant(".a"));
        CHECK_FALSE(isConstant(".0001"));
        CHECK_FALSE(isConstant(".001E1"));

        // Expoente Decimal
        CHECK_FALSE(isConstant("1.001E1.001"));
        CHECK_FALSE(isConstant("1.001E+1.00"));
        CHECK_FALSE(isConstant("1.001E-1.001"));
        CHECK_FALSE(isConstant("1.001E1."));

        // Espaços indevidos
        CHECK_FALSE(isConstant("1.1E 1"));
        CHECK_FALSE(isConstant("1.1 E1"));
        CHECK_FALSE(isConstant("1.1E 1"));
        CHECK_FALSE(isConstant("1. 1E1"));
        CHECK_FALSE(isConstant("1 .1E1"));

        // Sinal com espaço
        CHECK_FALSE(isConstant("+ 0"));
        CHECK_FALSE(isConstant("+ 1"));
        CHECK_FALSE(isConstant("+ 861654"));
        CHECK_FALSE(isConstant("+ 1E1"));
        CHECK_FALSE(isConstant("+ 1E+1"));
        CHECK_FALSE(isConstant("+ 20.0E-2"));
        CHECK_FALSE(isConstant("+ 123.001"));
        CHECK_FALSE(isConstant("- 0"));
        CHECK_FALSE(isConstant("- 1"));
        CHECK_FALSE(isConstant("- 861654"));
        CHECK_FALSE(isConstant("- 1E1"));
        CHECK_FALSE(isConstant("- 1E+1"));
        CHECK_FALSE(isConstant("- 20.0E-2"));
        CHECK_FALSE(isConstant("- 123.001"));
    }
}

TEST_CASE("isValidSign"){
    std::string prog = "12+12";
    CHECK_FALSE(isValidSign(prog,2,2));
    prog = "12 + 12";
    CHECK_FALSE(isValidSign(prog,4,4));

    prog = "12+ +12";
    CHECK_FALSE(isValidSign(prog,2,2));
    CHECK(isValidSign(prog,4,4));

    prog = "12+ -12";
    CHECK_FALSE(isValidSign(prog,2,2));
    CHECK(isValidSign(prog,4,4));

    prog = "12+(-12)";
    CHECK_FALSE(isValidSign(prog,2,2));
    CHECK(isValidSign(prog,4,4));

    prog = "1E+5";
    CHECK_FALSE(isValidSign(prog,2,2));
    prog = "5+1E+5";
    CHECK_FALSE(isValidSign(prog,1,1));
    prog = "5+(-1E+5)";
    CHECK(isValidSign(prog,3,3));
}