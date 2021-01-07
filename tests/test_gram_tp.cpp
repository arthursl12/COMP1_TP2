#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lex.h"
#include "parser.h"
#include "tp.h"

void clearSetStr(std::string str, 
                 std::string& program, 
                 std::vector<std::shared_ptr<Symbol>>& vec,
                 std::vector<std::string>& vals,
                 int& left, int& right)
{
    program.clear();
    program = str;
    vec.clear();
    vals.clear();
    left = 0;
    right = 0;
}

TEST_CASE("Tokens Simples"){
    int left = 0;
    int right = 0;
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    std::vector<std::string> values;
    Gramatica g;
    criaGramaticaTP2(g);

    clearSetStr("<=",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));
    
    clearSetStr(">",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));

    clearSetStr("div",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));

    clearSetStr("*",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));

    clearSetStr("or",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));
    
    clearSetStr("+",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));

    clearSetStr("log",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));

    clearSetStr("NOT",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK_FALSE(parser(tokens,g));
}

TEST_CASE("Tokens Simples"){
    int left = 0;
    int right = 0;
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    std::vector<std::string> values;
    Gramatica g;
    criaGramaticaTP2(g);

    SUBCASE("1"){
        clearSetStr("var",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("2"){
        clearSetStr("+1.22E-01",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
}


TEST_CASE("Expressões Simples"){
    std::string program;
    std::vector<std::string> values;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;
    Gramatica g;
    criaGramaticaTP2(g);

    SUBCASE("1"){
        clearSetStr("1+1",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("2"){
        clearSetStr("345+1.12",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("3"){
        clearSetStr("var*1",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("4"){
        clearSetStr("1.74E-5<=temp1",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("5"){
        clearSetStr("cst mod divider",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("6"){
        clearSetStr("sin (90)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
}

TEST_CASE("Questão dos Espaços"){
    std::string program;
    std::vector<std::string> values;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;
    Gramatica g;
    criaGramaticaTP2(g);

    SUBCASE("1"){
        clearSetStr("           1 +         1", program, tokens, values, left, right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("2"){
        clearSetStr("   cst        mod    divider       ",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("3"){
        clearSetStr("   cos90       ",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("4"){
        clearSetStr("   cos(90)       ",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("5"){
        clearSetStr("   cos     (   90 )       ",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
}

TEST_CASE("Expressões com Terminais Puros"){
    std::string program;
    std::vector<std::string> values;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;
    Gramatica g;
    criaGramaticaTP2(g);

    SUBCASE("1"){
        clearSetStr("1+(1)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("2"){
        clearSetStr("(1+1)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("3"){
        clearSetStr("cos(9.0E2-(2*var))",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("4"){
        clearSetStr("1+(1)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("5"){
        clearSetStr("1+(1)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
    SUBCASE("6"){
        clearSetStr("1+(1)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }

    SUBCASE("Correto e Corrige"){
        clearSetStr("1+1,7E10,cos(10,14)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));

        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));

        findTokens(program, tokens, values, left, right, false);
        CHECK_FALSE(parser(tokens,g));

        findTokens(program, tokens, values, left, right, false);
        CHECK_FALSE(parser(tokens,g));

        clearSetStr("1+1,7E10,cos(10),(14)",program,tokens,values,left,right);
        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));

        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));

        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));

        findTokens(program, tokens, values, left, right, false);
        CHECK(parser(tokens,g));
    }
}
/*

TEST_CASE("Questão do Sign"){
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    std::vector<std::string> values;
    int left = 0;
    int right = 0;
    Gramatica g;
    criaGramaticaTP2(g);

    clearSetStr("1+ +(1)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(parser(tokens,g));

    clearSetStr("1+ -var",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(parser(tokens,g));

    clearSetStr("1+(-var2)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(parser(tokens,g));

    clearSetStr("1 + -cos(2+4.0)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(parser(tokens,g));
}


TEST_CASE("Continuar de 'findTokens'"){
    int left = 0;
    int right = 0;
    std::vector<std::shared_ptr<Symbol>> symbols;
    std::vector<std::string> values;
    std::string entrada;
    Gramatica g;
    criaGramaticaTP2(g);

    entrada = "12+21,sin 90,tes*te";
    findTokens(entrada, symbols, values, left, right, false);
    CHECK(parser(symbols,g));

    symbols.clear();
    findTokens(entrada, symbols, values, left, right, false);
    CHECK(parser(symbols,g));

    symbols.clear();
    findTokens(entrada, symbols, values, left, right, false);
    CHECK(parser(symbols,g));
}
*/