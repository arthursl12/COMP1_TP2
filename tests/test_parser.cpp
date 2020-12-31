#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "gram.h"
#include "gram_exemplos.h"

#include <vector>
#include <memory>


TEST_CASE("Parser: gramática 0"){
    // E -> E+T | T
    // T -> T*F | F
    // F -> (E) | id

    SUBCASE("Entrada mais simples possível"){
        Gramatica g;
        cria_gram_0(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("id"));
        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Parênteses"){
        Gramatica g;
        cria_gram_0(g);

        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Erro"){
        Gramatica g;
        cria_gram_0(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        CHECK(parser(entrada, g) == false);
    }
    SUBCASE("Exemplo clássico"){
        Gramatica g;
        cria_gram_0(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("+"));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("*"));
        entrada.push_back(std::make_shared<Terminal>("id"));

        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Muitos parênteses"){
        Gramatica g;
        cria_gram_0(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));

        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Muitos parênteses v2.0"){
        Gramatica g;
        cria_gram_0(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>("*"));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("+"));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("*"));
        entrada.push_back(std::make_shared<Terminal>("id"));

        CHECK(parser(entrada, g) == true);
    }
}

TEST_CASE("Parser: gramática 1"){
    Gramatica g;
    cria_gram_1(g);

    SUBCASE("Entrada mais simples possível"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("id"));
        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Parênteses"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Erro"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        CHECK(parser(entrada, g) == false);
    }
    SUBCASE("Exemplo clássico"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("+"));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("*"));
        entrada.push_back(std::make_shared<Terminal>("id"));

        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Muitos parênteses"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));

        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Muitos parênteses v2.0"){  
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>(")"));
        entrada.push_back(std::make_shared<Terminal>("*"));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("+"));
        entrada.push_back(std::make_shared<Terminal>("id"));
        entrada.push_back(std::make_shared<Terminal>("*"));
        entrada.push_back(std::make_shared<Terminal>("id"));

        CHECK(parser(entrada, g) == true);
    }
}

TEST_CASE("Parser: gramática 7"){
    // S -> AaAb | BbBa
    // A -> (vazio)
    // B -> (vazio)
    SUBCASE("ab"){
        Gramatica g;
        cria_gram_7(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("b"));
        entrada.push_back(std::make_shared<Terminal>("a"));
        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Erro"){
        Gramatica g;
        cria_gram_7(g);
        
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("k"));
        entrada.push_back(std::make_shared<Terminal>("a"));
        CHECK(parser(entrada, g) == false);
    }
}

TEST_CASE("Parser: gramática 6"){
    // S -> (L) | a
    // L -> SL'
    // L' -> ,SL' | (vazio)

    Gramatica g;
    cria_gram_6(g);

    SUBCASE("Base"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("a"));
        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Um parâmetro"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>(")"));

        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Complexo"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>(","));
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>(","));
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>(")"));

        CHECK(parser(entrada, g) == true);
    }
    SUBCASE("Erros 1"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>(","));
        entrada.push_back(std::make_shared<Terminal>("a"));
        entrada.push_back(std::make_shared<Terminal>(","));
        entrada.push_back(std::make_shared<Terminal>(")"));

        CHECK(parser(entrada, g) == false);
    }
    SUBCASE("Erros 2"){
        std::vector<std::shared_ptr<Symbol>> entrada;
        entrada.push_back(std::make_shared<Terminal>("("));
        entrada.push_back(std::make_shared<Terminal>(","));
        entrada.push_back(std::make_shared<Terminal>(")"));

        CHECK(parser(entrada, g) == false);
    }
}








