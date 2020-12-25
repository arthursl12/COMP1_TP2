#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "gram.h"

#include <vector>
#include <memory>


TEST_CASE("FOLLOW: gramática 1"){
    SUBCASE("Caso E e E\'"){
        Gramatica g;
        cria_gram(g);

        // FOLLOW(E) = {$, )}
        std::set<Terminal> conj_follow;
        conj_follow.insert(Terminal("$"));
        conj_follow.insert(Terminal(")"));

        std::set<Terminal> out;
        std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("E");
        g.follow(nt, out);
        CHECK(out == conj_follow);

        // FOLLOW(E') = FOLLOW(E) = {$, )}
        out.clear();
        nt = std::make_shared<NaoTerminal>("E\'");
        g.follow(nt, out);
        CHECK(out == conj_follow);
    }
    SUBCASE("Caso T e T\'"){
        Gramatica g;
        cria_gram(g);

        // FOLLOW(T) = FIRST(E') U FOLLOW(E') = {+,$,)}
        std::set<Terminal> conj_follow;
        conj_follow.insert(Terminal("$"));
        conj_follow.insert(Terminal(")"));
        conj_follow.insert(Terminal("+"));

        std::set<Terminal> out;
        std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("T");
        g.follow(nt, out);
        CHECK(out == conj_follow);

        // FOLLOW(T') = FOLLOW(T) = {+,$,)}
        out.clear();
        nt = std::make_shared<NaoTerminal>("T\'");
        g.follow(nt, out);
        CHECK(out == conj_follow);
    }
    SUBCASE("Caso F"){
        Gramatica g;
        cria_gram(g);

        // FOLLOW(F) = FIRST(T') U FOLLOW(T') = {*,+,$,)}
        std::set<Terminal> conj_follow;
        conj_follow.insert(Terminal("$"));
        conj_follow.insert(Terminal(")"));
        conj_follow.insert(Terminal("+"));
        conj_follow.insert(Terminal("*"));


        std::set<Terminal> out;
        std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("F");
        g.follow(nt, out);
        CHECK(out == conj_follow);
    }
}


TEST_CASE("FOLLOW: gramática 3"){
    SUBCASE("Caso S: só o fim de palavra"){
        Gramatica g;
        cria_gram_3(g);

        // FOLLOW(S) = {$}
        std::set<Terminal> conj_follow;
        conj_follow.insert(Terminal("$"));

        std::set<Terminal> out;
        std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("S");
        g.follow(nt, out);
        CHECK(out == conj_follow);
    }SUBCASE("Caso A: genérico simples"){
        Gramatica g;
        cria_gram_3(g);

        // FOLLOW(A) = {a,c}
        std::set<Terminal> conj_follow;
        conj_follow.insert(Terminal("a"));
        conj_follow.insert(Terminal("c"));

        std::set<Terminal> out;
        std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("A");
        g.follow(nt, out);
        CHECK(out == conj_follow);
    }
}
