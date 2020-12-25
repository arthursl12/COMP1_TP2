#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "gram.h"
#include "gram_exemplos.h"

#include <vector>
#include <memory>

TEST_CASE("FIRST: gramática 1"){
    SUBCASE("Terminal"){
        Gramatica g;
        cria_gram_1(g);

        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("+"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("+");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Produção genérica simples"){
        Gramatica g;
        cria_gram_1(g);

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
        cria_gram_1(g);

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
        cria_gram_1(g);

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
        cria_gram_2(g);

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
        cria_gram_2(g);

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
        cria_gram_2(g);

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

TEST_CASE("FIRST: gramática 4"){
    SUBCASE("Caso E e F"){
        Gramatica g;
        cria_gram_4(g);

        // FIRST(E) = {g,(vazio)}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("g"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("E");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(F) = {f,(vazio)}
        conj_first.clear();
        conj_first.insert(Terminal("f"));
        conj_first.insert(Terminal(""));

        out.clear();
        sym = std::make_shared<NaoTerminal>("F");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso D"){
        Gramatica g;
        cria_gram_4(g);

        // FIRST(D) = {g,f,(vazio)}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("g"));
        conj_first.insert(Terminal("f"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("D");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso B e C"){
        Gramatica g;
        cria_gram_4(g);

        // FIRST(B) = {c}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("c"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("B");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(C) = {b,(vazio)}
        conj_first.clear();
        conj_first.insert(Terminal("b"));
        conj_first.insert(Terminal(""));

        out.clear();
        sym = std::make_shared<NaoTerminal>("C");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso S"){
        Gramatica g;
        cria_gram_4(g);

        // FIRST(S) = {a}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("a"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("S");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
}

TEST_CASE("FIRST: gramática 5"){
    SUBCASE("Caso B e C"){
        Gramatica g;
        cria_gram_5(g);

        // FIRST(B) = {b}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("b"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("B");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(C) = {g}
        conj_first.clear();
        conj_first.insert(Terminal("g"));

        out.clear();
        sym = std::make_shared<NaoTerminal>("C");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso A\'"){
        Gramatica g;
        cria_gram_5(g);

        // FIRST(A') = {d,(vazio)}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("d"));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("A\'");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso A e S"){
        Gramatica g;
        cria_gram_5(g);

        // FIRST(A) = {a}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("a"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("A");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(S) = FIRST(A) = {a}
        out.clear();
        sym = std::make_shared<NaoTerminal>("S");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
}


TEST_CASE("FIRST: gramática 6"){
    SUBCASE("Caso S e L"){
        Gramatica g;
        cria_gram_6(g);

        // FIRST(S) = {(,a}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("("));
        conj_first.insert(Terminal("a"));


        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("S");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(L) = FIRST(S) = {(,a}
        out.clear();
        sym = std::make_shared<NaoTerminal>("L");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso L\'"){
        Gramatica g;
        cria_gram_6(g);

        // FIRST(L') = { , ,(vazio)}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal(","));
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("L\'");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
}

TEST_CASE("FIRST: gramática 7"){
    SUBCASE("Caso A e B"){
        Gramatica g;
        cria_gram_7(g);

        // FIRST(A) = {(vazio)}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal(""));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("A");
        g.first(sym, out);
        CHECK(out == conj_first);

        // FIRST(B) = FIRST(A) = {(vazio)}
        out.clear();
        sym = std::make_shared<NaoTerminal>("B");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
    SUBCASE("Caso S"){
        Gramatica g;
        cria_gram_7(g);

        // FIRST(S) = FIRST(A) U {a} U FIRST(B) U {b} = {a,b}
        std::set<Terminal> conj_first;
        conj_first.insert(Terminal("a"));
        conj_first.insert(Terminal("b"));

        std::set<Terminal> out;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("S");
        g.first(sym, out);

        CHECK(out == conj_first);
    }
}