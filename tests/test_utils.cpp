#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "gram.h"

#include <vector>
#include <memory>

void cria_gram(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // E -> TE'
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<NaoTerminal>("E\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("E"), v);
    prods.push_back(p);

    // E' -> +TE' | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("+"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<NaoTerminal>("E\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("E\'"), v);
    prods.push_back(p);

    // T -> FT'
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    cad.push_back(std::make_shared<NaoTerminal>("T\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("T"), v);
    prods.push_back(p);

    // T' -> *FT' | (vazio)
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("*"));
    cad.push_back(std::make_shared<NaoTerminal>("F"));
    cad.push_back(std::make_shared<NaoTerminal>("T\'"));
    v.push_back(std::make_shared<Cadeia>(cad));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("T\'"), v);
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

    gram = Gramatica(prods);
}

void cria_outra_gram(Gramatica& gram){
    std::vector<std::shared_ptr<Producao>> prods;
    prods.clear();

    std::vector<std::shared_ptr<Cadeia>> v;
    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Producao> p;

    // C -> h | (vazio)
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("h");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("C"), v);
    prods.push_back(p);

    // B -> g | (vazio)
    v.clear();
    cad.clear();
    sym = std::make_shared<Terminal>("g");
    v.push_back(std::make_shared<Cadeia>(sym));
    sym = std::make_shared<Terminal>("");
    v.push_back(std::make_shared<Cadeia>(sym));
    p = std::make_shared<Producao>(NaoTerminal("B"), v);
    prods.push_back(p);
    
    // A -> da | BC
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("d"));
    cad.push_back(std::make_shared<Terminal>("a"));
    v.push_back(std::make_shared<Cadeia>(cad));
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("A"), v);
    prods.push_back(p);

    // A -> da | BC
    v.clear();
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("A"));
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    v.push_back(std::make_shared<Cadeia>(cad));

    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("C"));
    cad.push_back(std::make_shared<Terminal>("b"));
    cad.push_back(std::make_shared<Terminal>("b"));
    v.push_back(std::make_shared<Cadeia>(cad));

    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("B"));
    cad.push_back(std::make_shared<Terminal>("a"));
    v.push_back(std::make_shared<Cadeia>(cad));
    p = std::make_shared<Producao>(NaoTerminal("S"), v);
    prods.push_back(p);

    gram = Gramatica(prods);
}

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
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("T\'");
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
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("B");
        g.first(sym, out);
        CHECK(out == conj_first);
    }
}