#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "gram.h"
#include "gram_exemplos.h"

#include <vector>
#include <memory>

TEST_CASE("FIRST: gramática 1"){
    SUBCASE("Terminal"){
        Gramatica g;
        cria_gram(g);

        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("+"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("+");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Produção genérica simples"){
        Gramatica g;
        cria_gram(g);

        // FIRST(F) = {(,id}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("("));
        conj_first.insert(Terminal("id"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("F");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Produção com string, recursivamente"){
        Gramatica g;
        cria_gram(g);

        // FIRST(T) = FIRST(E) = FIRST(F) = {(,id}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("("));
        conj_first.insert(Terminal("id"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("T");
        g.first(sym, out);
        CHECK(out == conj_first);

        out.clear();
        sym = std::make_shared<NaoTerminal>("E");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Produção com vazio"){
        Gramatica g;
        cria_gram(g);

        // FIRST(E') = {+,(vazio)}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("+"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("E\'");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(T') = {*,(vazio)}
        conj_first.clear();
        conj_first.insert(Terminal("*"));
        conj_first.insert(Terminal(""));

        out.clear();
        sym = std::make_shared<NaoTerminal>("T\'");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
}

TEST_CASE("FIRST: gramática 2"){
    SUBCASE("Produção com string, string com vazio, várias produções"){
        Gramatica g;
        cria_outra_gram(g);

        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("a"));
        conj_first.insert(Terminal("b"));
        conj_first.insert(Terminal("d"));
        conj_first.insert(Terminal("g"));
        conj_first.insert(Terminal("h"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("S");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Produção com string e vazio"){
        Gramatica g;
        cria_outra_gram(g);

        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("d"));
        conj_first.insert(Terminal("g"));
        conj_first.insert(Terminal("h"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("A");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Produções com vazio"){
        Gramatica g;
        cria_outra_gram(g);

        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("h"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("C");
        g.first(sym, out);
        CHECK(out == conj_first);

        conj_first.clear();
        conj_first.insert(Terminal("g"));
        conj_first.insert(Terminal(""));
        out.clear();
        sym = std::make_shared<NaoTerminal>("B");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
}
