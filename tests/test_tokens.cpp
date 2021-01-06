#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lex.h"

/*
TOKENS:
RELOP, ADDOP, MULOP, SPECOP, identifier, constant, NOT

N-Ts: 
EXPR_LS, EXPR, S_EXPR, T, FA, FR, S

T-s:
(, ), ,, +, - 
*/

void clearSetStr(std::string str, 
                 std::string& program, 
                 std::vector<std::shared_ptr<Symbol>>& vec,
                 int& left, int& right)
{
    program.clear();
    program = str;
    vec.clear();
    left = 0;
    right = 0;
}

TEST_CASE("Tokens Simples"){
    int left = 0;
    int right = 0;
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;

    clearSetStr("+1.22E-01",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));

    clearSetStr("<=",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("RELOP"));
    
    clearSetStr(">",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("RELOP"));

    clearSetStr("div",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("MULOP"));

    clearSetStr("*",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("MULOP"));

    clearSetStr("or",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("ADDOP"));
    
    clearSetStr("+",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("ADDOP"));

    clearSetStr("log",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));

    clearSetStr("var",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("id"));

    clearSetStr("NOT",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("NOT"));
}


TEST_CASE("Expressões Simples"){
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;

    clearSetStr("1+1",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));

    clearSetStr("345+1.12",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));

    clearSetStr("var*1",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(*tokens[1] == Terminal("MULOP"));
    CHECK(*tokens[2] == Terminal("constant"));

    clearSetStr("1.74E-5<=temp1",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("RELOP"));
    CHECK(*tokens[2] == Terminal("id"));

    clearSetStr("cst mod divider",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(*tokens[1] == Terminal("MULOP"));
    CHECK(*tokens[2] == Terminal("id"));

    clearSetStr("sin 90",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("constant"));
}

TEST_CASE("Questão dos Espaços"){
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;

    clearSetStr("           1 +         1", program, tokens, left, right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));

    clearSetStr("   cst        mod    divider       ",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(*tokens[1] == Terminal("MULOP"));
    CHECK(*tokens[2] == Terminal("id"));

    clearSetStr("   cos      90       ",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("constant"));

    clearSetStr("   cos90       ",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("id"));

    
    clearSetStr("   cos(90)       ",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(*tokens[3] == Terminal(")"));

    clearSetStr("   cos     (   90 )       ",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(*tokens[3] == Terminal(")"));
}

TEST_CASE("Expressões com Terminais Puros"){
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;

    clearSetStr("1+(1)",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("("));
    CHECK(*tokens[3] == Terminal("constant"));
    CHECK(*tokens[4] == Terminal(")"));

    clearSetStr("(1+1)",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("("));
    CHECK(*tokens[1] == Terminal("constant"));
    CHECK(*tokens[2] == Terminal("ADDOP"));
    CHECK(*tokens[3] == Terminal("constant"));
    CHECK(*tokens[4] == Terminal(")"));

    clearSetStr("cos(9.0E2-(2*var))",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(*tokens[3] == Terminal("ADDOP"));
    CHECK(*tokens[4] == Terminal("("));
    CHECK(*tokens[5] == Terminal("constant"));
    CHECK(*tokens[6] == Terminal("MULOP"));
    CHECK(*tokens[7] == Terminal("id"));
    CHECK(*tokens[8] == Terminal(")"));
    CHECK(*tokens[9] == Terminal(")"));

    clearSetStr("1+1,7E10,cos(10,14)",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));
    // left = 0; right = 0;
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    // left = 0; right = 0;
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    // left = 0; right = 0;
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal(")"));
}

TEST_CASE("Questão do Sign"){
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;
    
    clearSetStr("1+ +(1)",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("+"));
    CHECK(*tokens[3] == Terminal("("));
    CHECK(*tokens[4] == Terminal("constant"));
    CHECK(*tokens[5] == Terminal(")"));

    clearSetStr("1+ -var",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("-"));
    CHECK(*tokens[3] == Terminal("id"));

    clearSetStr("1+(-var2)",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("("));
    CHECK(*tokens[3] == Terminal("-"));
    CHECK(*tokens[4] == Terminal("id"));
    CHECK(*tokens[5] == Terminal(")"));

    clearSetStr("1 + -cos(2+4.0)",program,tokens,left,right);
    findTokens(program, tokens, left, right);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("-"));
    CHECK(*tokens[3] == Terminal("SPECOP"));
    CHECK(*tokens[4] == Terminal("("));
    CHECK(*tokens[5] == Terminal("constant"));
    CHECK(*tokens[6] == Terminal("ADDOP"));
    CHECK(*tokens[7] == Terminal("constant"));
    CHECK(*tokens[8] == Terminal(")"));
}

TEST_CASE("Retorno de 'findTokens'"){
    int left = 0;
    int right = 0;
    std::vector<std::shared_ptr<Symbol>> symbols;
    std::string entrada;

    entrada = "12+21,sen 90";
    CHECK(findTokens(entrada, symbols, left, right));
    CHECK(left == 6);
    CHECK(right == 6);

    left = 0;
    right = 0;
    entrada = "12+21";
    CHECK_FALSE(findTokens(entrada, symbols, left, right));
    CHECK(left == 5);
    CHECK(right == 6);

    left = 0;
    right = 0;
    entrada = "12+21,";
    CHECK_THROWS(findTokens(entrada, symbols, left, right));
    CHECK(left == 6);
    CHECK(right == 6);

    left = 0;
    right = 0;
    entrada = "12 + 21 , sen 90, tes*te";
    CHECK(findTokens(entrada, symbols, left, right));
    CHECK(left == 9);
    CHECK(right == 9);
}

TEST_CASE("Continuar de 'findTokens'"){
    int left = 0;
    int right = 0;
    std::vector<std::shared_ptr<Symbol>> symbols;
    std::string entrada;

    entrada = "12+21,sin 90,tes*te";
    CHECK(findTokens(entrada, symbols, left, right));
    CHECK(symbols.size() == 3);
    CHECK(*symbols[0] == Terminal("constant"));
    CHECK(*symbols[1] == Terminal("ADDOP"));
    CHECK(*symbols[2] == Terminal("constant"));

    symbols.clear();
    CHECK(findTokens(entrada, symbols, left, right));
    CHECK(symbols.size() == 2);
    CHECK(*symbols[0] == Terminal("SPECOP"));
    CHECK(*symbols[1] == Terminal("constant"));

    symbols.clear();
    CHECK_FALSE(findTokens(entrada, symbols, left, right));
    CHECK(symbols.size() == 3);
    CHECK(*symbols[0] == Terminal("id"));
    CHECK(*symbols[1] == Terminal("MULOP"));
    CHECK(*symbols[2] == Terminal("id"));
}

