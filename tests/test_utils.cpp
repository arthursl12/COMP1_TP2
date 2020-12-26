#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "gram.h"

#include <vector>
#include <memory>
#include "gram_exemplos.h"


TEST_CASE("Utils: gramaticaEstendida"){
    Gramatica g1;
    cria_gram_1(g1);

    std::set<Terminal> ts1;
    g1.conjuntoTerminais(ts1);

    std::set<NaoTerminal> nt1;
    g1.conjuntoNaoTerminais(nt1);

    gramaticaEstendida(g1);
    std::set<Terminal> ts2;
    g1.conjuntoTerminais(ts2);

    std::set<NaoTerminal> nt2;
    g1.conjuntoNaoTerminais(nt2);

    CHECK(ts1 != ts2);
    ts2.erase(Terminal("."));
    CHECK(ts1 == ts2);

    CHECK(nt1 != nt2);
    nt2.erase(NaoTerminal("S\'"));
    CHECK(nt1 == nt2);

}
