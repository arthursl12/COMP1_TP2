#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cadeia.h"
#include "prod.h"
#include "gram.h"

#include <vector>
#include <memory>


/*
Conjunto de Terminais
Conjunto de Nomes de produção
Integridade das produções (todas referenciadas existem)
*/
void producoes(std::vector<std::shared_ptr<Producao>>& prods){
    prods.clear();

    // E' -> E
    std::vector<std::shared_ptr<Cadeia>> v;
    std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("E");
    v.push_back(std::make_shared<Cadeia>(sym));
    std::shared_ptr<Producao> p = \
        std::make_shared<Producao>(NaoTerminal("E\'"), v);
    prods.push_back(p);

    // E -> E+T | T
    v.clear();
    std::vector<std::shared_ptr<Symbol>> cad;
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    cad.push_back(std::make_shared<Terminal>("+"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<NaoTerminal>("T");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("E"), v);
    prods.push_back(p);

    // T -> T*F | F
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<Terminal>("*"));
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<NaoTerminal>("F");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("T"), v);
    prods.push_back(p);

    // F -> (E) | id
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("("));
    cad.push_back(std::make_shared<NaoTerminal>("E"));
    cad.push_back(std::make_shared<Terminal>(")"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("id");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("F"), v);
    prods.push_back(p);
}

TEST_CASE("Gramática: construção"){
    std::vector<std::shared_ptr<Producao>> prods;
    producoes(prods);
    for (auto it = prods.begin(); it != prods.end(); it++){
        std::cout << (**it) << std::endl;
    }
    // CHECK_NOTHROW(Gramatica(prods));
}