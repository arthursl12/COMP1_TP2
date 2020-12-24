#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cadeia.h"
#include "prod.h"
#include "doctest.h"
#include <vector>

TEST_CASE("Produção: construção"){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    CHECK_NOTHROW(Producao(NaoTerminal("B1"),prods));
}


void criaProducao(Producao& out){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    out = Producao(NaoTerminal("B1"),prods);
}

TEST_CASE("Produção: atributos"){
    Producao p;
    criaProducao(p);
    CHECK(p.label() == NaoTerminal("B1"));

}

TEST_CASE("Produção: acesso"){
    std::vector<std::shared_ptr<Cadeia>> prods;
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    prods.push_back(std::make_shared<Cadeia>(p1));
    p1 = std::make_shared<Terminal>("a");
    prods.push_back(std::make_shared<Cadeia>(p1));

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    prods.push_back(std::make_shared<Cadeia>(v1));

    Producao p = Producao(NaoTerminal("B1"),prods);

    p1 = std::make_shared<Terminal>("");
    CHECK(p[0] == Cadeia(p1));
    p1 = std::make_shared<Terminal>("a");
    CHECK(p[1] == Cadeia(p1));
    CHECK(p[2] == Cadeia(v1));
    CHECK_THROWS(p[3]);
}