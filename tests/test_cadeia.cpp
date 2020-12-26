#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "symbol.h"
#include "cadeia.h"
#include "doctest.h"

#include <vector>
#include <memory>

TEST_CASE("Cadeia: construção"){
    SUBCASE("Construtor Simples"){
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        CHECK_NOTHROW(Cadeia p1);
    }
    SUBCASE("Construir via vetor"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        CHECK_NOTHROW(Cadeia v1);
    }
    SUBCASE("Construtor default"){
        CHECK_NOTHROW(Cadeia());
    }
}

TEST_CASE("Cadeia: operador []"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        Cadeia c = Cadeia(v1);

        CHECK(c[0] == Terminal("a"));
        CHECK(c[1] == Terminal("b"));
        CHECK(c[5] == NaoTerminal("B1"));
        CHECK_THROWS(c[10]);
}

TEST_CASE("Cadeia: tamanho da cadeia"){
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    CHECK(Cadeia(p1).qtdSimbolos() == 0);
    
    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    CHECK(Cadeia(v1).qtdSimbolos() == 6);
    
    CHECK(Cadeia().qtdSimbolos() == 0);
}

TEST_CASE("Cadeia: operador comparação igualdade"){
        SUBCASE("Qtd elementos"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("b"));
            Cadeia c2 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c3 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
            CHECK_FALSE(c1 == c3);
        }
        SUBCASE("Tipo dos elementos"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<NaoTerminal>("a"));
            v1.push_back(std::make_shared<NaoTerminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c2 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
        }
        SUBCASE("Teste simples"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c2 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("a"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<Terminal>("b"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            v1.push_back(std::make_shared<NaoTerminal>("B1"));
            Cadeia c3 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
            CHECK(c1 == c3);
        }
        SUBCASE("Teste simples Não-terminal"){
            std::vector<std::shared_ptr<Symbol>> v1;
            v1.push_back(std::make_shared<Terminal>("A"));
            v1.push_back(std::make_shared<Terminal>("C"));
            Cadeia c1 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("C"));
            v1.push_back(std::make_shared<Terminal>("C"));
            Cadeia c2 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("A"));
            v1.push_back(std::make_shared<Terminal>("B"));
            Cadeia c3 = Cadeia(v1);

            v1.clear();
            v1.push_back(std::make_shared<Terminal>("A"));
            v1.push_back(std::make_shared<Terminal>("C"));
            Cadeia c4 = Cadeia(v1);

            CHECK_FALSE(c1 == c2);
            CHECK_FALSE(c1 == c3);
            CHECK_FALSE(c1 == c2);
            CHECK(c1 == c4);
        }
}

TEST_CASE("Cadeia: print"){
    std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
    CHECK_NOTHROW(std::cout << Cadeia(p1) << std::endl);

    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    CHECK_NOTHROW(std::cout << Cadeia(v1) << std::endl);

    CHECK_NOTHROW(std::cout << Cadeia() << std::endl);
}

TEST_CASE("Cadeia: conjunto terminais"){
    SUBCASE("Geral"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        Cadeia c = Cadeia(v1);

        std::set<Terminal> conj_terminais;
        conj_terminais.insert(Terminal("a"));
        conj_terminais.insert(Terminal("b"));

        std::set<Terminal> out;;
        c.conjuntoTerminais(out);
        CHECK(out == conj_terminais);
    }
    SUBCASE("Vazio1"){
        std::vector<std::shared_ptr<Symbol>> v1;
        Cadeia c = Cadeia(v1);
        std::set<Terminal> conj_terminais;
        std::set<Terminal> out;
        c.conjuntoTerminais(out);
        CHECK(out == conj_terminais);
        CHECK(out.empty() == true);
        CHECK(v1.empty());
        CHECK(conj_terminais.empty());
    }
    SUBCASE("Vazio2"){
        Cadeia c = Cadeia();

        std::set<Terminal> conj_terminais;
        std::set<Terminal> out;
        c.conjuntoTerminais(out);
        CHECK(out == conj_terminais);
        CHECK(out.empty() == true);
        CHECK(conj_terminais.empty());
    }

}

TEST_CASE("Cadeia: conjunto não-terminais"){
    SUBCASE("Geral"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<NaoTerminal>("B2"));
        Cadeia c = Cadeia(v1);

        std::set<NaoTerminal> conj_n_terminais;
        conj_n_terminais.insert(NaoTerminal("B1"));
        conj_n_terminais.insert(NaoTerminal("B2"));

        std::set<NaoTerminal> out;
        c.conjuntoNaoTerminais(out);
        CHECK(out == conj_n_terminais);
    }
    SUBCASE("Vazio1"){
        std::vector<std::shared_ptr<Symbol>> v1;
        Cadeia c = Cadeia(v1);
        std::set<NaoTerminal> conj_n_terminais;
        std::set<NaoTerminal> out;
        c.conjuntoNaoTerminais(out);
        CHECK(out == conj_n_terminais);
        CHECK(out.empty() == true);
        CHECK(v1.empty());
        CHECK(conj_n_terminais.empty());
    }
    SUBCASE("Vazio2"){
        Cadeia c = Cadeia();

        std::set<NaoTerminal> conj_n_terminais;
        std::set<NaoTerminal> out;
        c.conjuntoNaoTerminais(out);
        CHECK(out == conj_n_terminais);
        CHECK(out.empty() == true);
        CHECK(conj_n_terminais.empty());
    }
}

TEST_CASE("Cadeia: find e end"){
    SUBCASE("Cadeias Vazias"){
        std::shared_ptr<Symbol> p1 = std::make_shared<Terminal>("");
        std::shared_ptr<NaoTerminal> sym = std::make_shared<NaoTerminal>("C");

        Cadeia p = Cadeia(p1);
        CHECK(p.find(sym) == p.end());

        p = Cadeia();
        CHECK(p.find(sym) == p.end());
    }
    SUBCASE("Cadeia com terminais"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<Terminal>("b"));
        Cadeia c = Cadeia(v1);

        std::shared_ptr<NaoTerminal> sym = std::make_shared<NaoTerminal>("B1");
        CHECK(c.find(sym) == c.end());
    }
    SUBCASE("Construir via vetor"){
        std::vector<std::shared_ptr<Symbol>> v1;
        v1.push_back(std::make_shared<Terminal>("a"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        v1.push_back(std::make_shared<Terminal>("b"));
        v1.push_back(std::make_shared<NaoTerminal>("C"));
        v1.push_back(std::make_shared<NaoTerminal>("B1"));
        Cadeia c = Cadeia(v1);

        std::shared_ptr<NaoTerminal> sym = std::make_shared<NaoTerminal>("B1");

        CHECK(**c.find(sym) == *std::make_shared<NaoTerminal>("B1"));

        sym = std::make_shared<NaoTerminal>("C");
        CHECK(**c.find(sym) == *std::make_shared<NaoTerminal>("C"));

        sym = std::make_shared<NaoTerminal>("D");
        CHECK(c.find(sym) == c.end());
    }
}

TEST_CASE("Cadeia: find com pos"){
    std::vector<std::shared_ptr<Symbol>> v1;
    v1.push_back(std::make_shared<Terminal>("a"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    v1.push_back(std::make_shared<Terminal>("b"));
    v1.push_back(std::make_shared<NaoTerminal>("C"));
    v1.push_back(std::make_shared<NaoTerminal>("B1"));
    Cadeia c = Cadeia(v1);

    std::shared_ptr<NaoTerminal> sym = std::make_shared<NaoTerminal>("B1");
    auto it1 = c.find(sym);
    auto it2 = c.find(sym,it1);
    CHECK(**it2 == *std::make_shared<NaoTerminal>("B1"));
    CHECK(it1 != it2);

    auto it3 = c.find(sym,it2);
    CHECK(it3 == c.end());
}