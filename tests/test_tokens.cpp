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

    clearSetStr("+1.22E-01",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(values[0] == "+1.22E-01");

    clearSetStr("<=",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("RELOP"));
    CHECK(values[0] == "<=");
    
    clearSetStr(">",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("RELOP"));
    CHECK(values[0] == ">");

    clearSetStr("div",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("MULOP"));
    CHECK(values[0] == "div");

    clearSetStr("*",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("MULOP"));
    CHECK(values[0] == "*");

    clearSetStr("or",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("ADDOP"));
    CHECK(values[0] == "or");
    
    clearSetStr("+",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("ADDOP"));

    clearSetStr("log",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(values[0] == "log");

    clearSetStr("var",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(values[0] == "var");

    clearSetStr("NOT",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("NOT"));
    CHECK(values[0] == "NOT");
}


TEST_CASE("Expressões Simples"){
    std::string program;
    std::vector<std::string> values;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;

    clearSetStr("1+1",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(values[0] == "1");
    CHECK(values[1] == "+");
    CHECK(values[2] == "1");

    clearSetStr("345+1.12",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(values[0] == "345");
    CHECK(values[1] == "+");
    CHECK(values[2] == "1.12");

    clearSetStr("var*1",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(*tokens[1] == Terminal("MULOP"));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(values[0] == "var");
    CHECK(values[1] == "*");
    CHECK(values[2] == "1");

    clearSetStr("1.74E-5<=temp1",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("RELOP"));
    CHECK(*tokens[2] == Terminal("id"));
    CHECK(values[0] == "1.74E-5");
    CHECK(values[1] == "<=");
    CHECK(values[2] == "temp1");

    clearSetStr("cst mod divider",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(*tokens[1] == Terminal("MULOP"));
    CHECK(*tokens[2] == Terminal("id"));
    CHECK(values[0] == "cst");
    CHECK(values[1] == "mod");
    CHECK(values[2] == "divider");

    clearSetStr("sin 90",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("constant"));
    CHECK(values[0] == "sin");
    CHECK(values[1] == "90");
}

TEST_CASE("Questão dos Espaços"){
    std::string program;
    std::vector<std::string> values;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;

    clearSetStr("           1 +         1", program, tokens, values, left, right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));

    clearSetStr("   cst        mod    divider       ",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("id"));
    CHECK(*tokens[1] == Terminal("MULOP"));
    CHECK(*tokens[2] == Terminal("id"));

    clearSetStr("   cos      90       ",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("constant"));

    clearSetStr("   cos90       ",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("id"));

    
    clearSetStr("   cos(90)       ",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(*tokens[3] == Terminal(")"));

    clearSetStr("   cos     (   90 )       ",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    CHECK(*tokens[3] == Terminal(")"));
}

TEST_CASE("Expressões com Terminais Puros"){
    std::string program;
    std::vector<std::string> values;
    std::vector<std::shared_ptr<Symbol>> tokens;
    int left = 0;
    int right = 0;

    clearSetStr("1+(1)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("("));
    CHECK(*tokens[3] == Terminal("constant"));
    CHECK(*tokens[4] == Terminal(")"));

    clearSetStr("(1+1)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("("));
    CHECK(*tokens[1] == Terminal("constant"));
    CHECK(*tokens[2] == Terminal("ADDOP"));
    CHECK(*tokens[3] == Terminal("constant"));
    CHECK(*tokens[4] == Terminal(")"));

    clearSetStr("cos(9.0E2-(2*var))",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
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

    clearSetStr("1+1,7E10,cos(10,14)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("constant"));
    // left = 0; right = 0;
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    // left = 0; right = 0;
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("SPECOP"));
    CHECK(*tokens[1] == Terminal("("));
    CHECK(*tokens[2] == Terminal("constant"));
    // left = 0; right = 0;
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal(")"));
}

TEST_CASE("Questão do Sign"){
    std::string program;
    std::vector<std::shared_ptr<Symbol>> tokens;
    std::vector<std::string> values;
    int left = 0;
    int right = 0;
    
    clearSetStr("1+ +(1)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("+"));
    CHECK(*tokens[3] == Terminal("("));
    CHECK(*tokens[4] == Terminal("constant"));
    CHECK(*tokens[5] == Terminal(")"));

    clearSetStr("1+ -var",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("-"));
    CHECK(*tokens[3] == Terminal("id"));

    clearSetStr("1+(-var2)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
    CHECK(*tokens[0] == Terminal("constant"));
    CHECK(*tokens[1] == Terminal("ADDOP"));
    CHECK(*tokens[2] == Terminal("("));
    CHECK(*tokens[3] == Terminal("-"));
    CHECK(*tokens[4] == Terminal("id"));
    CHECK(*tokens[5] == Terminal(")"));

    clearSetStr("1 + -cos(2+4.0)",program,tokens,values,left,right);
    findTokens(program, tokens, values, left, right, false);
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
    std::vector<std::string> values;
    std::string entrada;

    entrada = "12+21,sen 90";
    CHECK(findTokens(entrada, symbols, values, left, right, false));
    CHECK(left == 6);
    CHECK(right == 6);

    left = 0;
    right = 0;
    entrada = "12+21";
    CHECK_FALSE(findTokens(entrada, symbols, values, left, right, false));
    CHECK(left == 5);
    CHECK(right == 6);

    left = 0;
    right = 0;
    entrada = "12+21,";
    CHECK_THROWS(findTokens(entrada, symbols, values, left, right, false));
    CHECK(left == 6);
    CHECK(right == 6);

    left = 0;
    right = 0;
    entrada = "12 + 21 , sen 90, tes*te";
    CHECK(findTokens(entrada, symbols, values, left, right, false));
    CHECK(left == 9);
    CHECK(right == 9);
}

TEST_CASE("Continuar de 'findTokens'"){
    int left = 0;
    int right = 0;
    std::vector<std::shared_ptr<Symbol>> symbols;
    std::vector<std::string> values;
    std::string entrada;

    entrada = "12+21,sin 90,tes*te";
    CHECK(findTokens(entrada, symbols, values, left, right, false));
    CHECK(symbols.size() == 3);
    CHECK(*symbols[0] == Terminal("constant"));
    CHECK(*symbols[1] == Terminal("ADDOP"));
    CHECK(*symbols[2] == Terminal("constant"));

    symbols.clear();
    CHECK(findTokens(entrada, symbols, values, left, right, false));
    CHECK(symbols.size() == 2);
    CHECK(*symbols[0] == Terminal("SPECOP"));
    CHECK(*symbols[1] == Terminal("constant"));

    symbols.clear();
    CHECK_FALSE(findTokens(entrada, symbols, values, left, right, false));
    CHECK(symbols.size() == 3);
    CHECK(*symbols[0] == Terminal("id"));
    CHECK(*symbols[1] == Terminal("MULOP"));
    CHECK(*symbols[2] == Terminal("id"));
}

