#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "symbol.h"
#include "cadeia.h"
#include "conj.h"
#include "doctest.h"

#include "closure_goto.h"
#include "conj_itens.h"

#include <vector>
#include <memory>

TEST_CASE("ConjuntoItens: construção"){
    SUBCASE("Construtor Simples"){
        CHECK_NOTHROW(ConjuntoItens());
    }
}

TEST_CASE("ConjuntoItens: getters/insert"){
    SUBCASE("Caso default"){
        ConjuntoItens c = ConjuntoItens();
        std::set<std::string> conj;
        c.getLabels(conj);
        CHECK(*conj.find("I0") == "I0");
        CHECK(c.qtdConjuntos() == 1);
    }
    SUBCASE("Geral"){
        std::set<std::set<std::shared_ptr<Item>>> out;
        out.clear();
        cria_sets_manual(out);

        ConjuntoItens c;
        for (auto conj: out)
            c.insert(conj);

        std::set<std::string> conj;
        c.getLabels(conj);
        CHECK(*conj.find("I0") == "I0");
        CHECK(*conj.find("I1") == "I1");
        CHECK(*conj.find("I2") == "I2");
        CHECK(*conj.find("I3") == "I3");
        CHECK(*conj.find("I4") == "I4");
        CHECK(*conj.find("I5") == "I5");
        CHECK(*conj.find("I6") == "I6");
        CHECK(*conj.find("I7") == "I7");
        CHECK(*conj.find("I8") == "I8");
        CHECK(*conj.find("I9") == "I9");
        CHECK(*conj.find("I10") == "I10");
        CHECK(*conj.find("I11") == "I11");
        CHECK(c.qtdConjuntos() == 12);
    }
}

TEST_CASE("ConjuntosItens: busca"){
    SUBCASE("Sem conjuntos"){
        ConjuntoItens c = ConjuntoItens();
        auto it = c.begin();
        it++;
        CHECK(it == c.end());

        std::set<std::set<std::shared_ptr<Item>>> out;
        out.clear();
        cria_sets_manual(out);
        for (auto conj: out){
            CHECK(c.find(conj) == c.end());
        }
    }
    SUBCASE("Geral"){
        std::set<std::set<std::shared_ptr<Item>>> out;
        out.clear();
        cria_sets_manual(out);

        ConjuntoItens c;
        for (auto conj: out){
            c.insert(conj);
        }

        for (auto conj: out){
            CHECK(c.find(conj) != c.end());
            // CHECK(*c.find(conj) == conj);
        }
    }   
}
