#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "tabelas.h"
#include "gram.h"
#include "item.h"
#include "action.h"

#include <vector>
#include <memory>
#include "gram_exemplos.h"
#include "closure_goto.h"
#include "conj_itens.h"
#include "action_goto.h"


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

    CHECK(ts1 == ts2);

    CHECK(nt1 != nt2);
    nt2.erase(NaoTerminal("S\'"));
    CHECK(nt1 == nt2);
}


TEST_CASE("Utils: closure"){
    SUBCASE("Exemplo simples"){
        Gramatica g;
        cria_gram_1(g);
        gramaticaEstendida(g);

        std::set<std::shared_ptr<Item>> conjI0;
        std::vector<std::shared_ptr<Cadeia>> v;
        std::vector<std::shared_ptr<Symbol>> cad;
        std::shared_ptr<Symbol> sym;
        std::shared_ptr<Producao> p;

        // S' -> .E
        v.clear();
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("E"));
        v.push_back(std::make_shared<Cadeia>(cad));
        p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
        std::shared_ptr<Item> it0 = std::make_shared<Item>(*p); 
        conjI0.insert(it0);

        closure(conjI0, g);
        std::set<std::shared_ptr<Item>> out;
        cria_closure_manual(out);
        out.insert(it0);

        CHECK(conjuntosIguais(out,conjI0));
    }
    SUBCASE("Exemplo GeeksForGeeks: caso S"){
        Gramatica g;
        cria_gram_closure_1(g);
        gramaticaEstendida(g);

        std::set<std::shared_ptr<Item>> conjI0;
        std::vector<std::shared_ptr<Cadeia>> v;
        std::vector<std::shared_ptr<Symbol>> cad;
        std::shared_ptr<Symbol> sym;
        std::shared_ptr<Producao> p;

        // S' -> .S (item)
        v.clear();
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("S"));
        v.push_back(std::make_shared<Cadeia>(cad));
        p = std::make_shared<Producao>(NaoTerminal("S\'"), v);
        std::shared_ptr<Item> it0 = std::make_shared<Item>(*p); 
        conjI0.insert(it0);

        closure(conjI0, g);
        std::set<std::shared_ptr<Item>> out;
        cria_closure_manual_1(out);

        CHECK(conjuntosIguais(out,conjI0));
    }
    SUBCASE("Exemplo GeeksForGeeks: caso A.A"){
        Gramatica g;
        cria_gram_closure_1(g);
        gramaticaEstendida(g);

        std::set<std::shared_ptr<Item>> conjI0;
        std::vector<std::shared_ptr<Cadeia>> v;
        std::vector<std::shared_ptr<Symbol>> cad;
        std::shared_ptr<Symbol> sym;
        std::shared_ptr<Producao> p;

        // S -> .AA (item)
        v.clear();
        cad.clear();
        cad.push_back(std::make_shared<NaoTerminal>("A"));
        cad.push_back(std::make_shared<NaoTerminal>("A"));
        v.push_back(std::make_shared<Cadeia>(cad));
        p = std::make_shared<Producao>(NaoTerminal("S"), v);
        std::shared_ptr<Item> it0 = std::make_shared<Item>(*p); 
        
        // S -> A.A 
        it0->avanca();
        conjI0.insert(it0);

        closure(conjI0, g);
        std::set<std::shared_ptr<Item>> out;
        cria_closure_manual_2(out);
        
        // std::cout << "CONJI0:" << std::endl;
        // for (auto elm0 : conjI0){
        //     std::cout << "\t" << *elm0 << std::endl;
        // }
        // std::cout << "OUT:" << std::endl;
        // for (auto elm0 : out){
        //     std::cout << "\t" << *elm0 << std::endl;
        // }
        CHECK(conjuntosIguais(out,conjI0));
    }
}

TEST_CASE("Utils: goto"){
    SUBCASE("Exemplo do livro"){
        Gramatica g;
        cria_gram_goto(g);
        gramaticaEstendida(g);

        std::set<std::shared_ptr<Item>> conjI0;
        std::set<std::shared_ptr<Item>> out;
        cria_goto_manual(conjI0, out);

        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("+");
        std::set<std::shared_ptr<Item>> conj_goto;
        funcaoGoto(conjI0, sym, g, conj_goto);

        CHECK(conjuntosIguais(out,conj_goto));
    }
    SUBCASE("Exemplo GeeksForGeeks: caso .AA"){
        Gramatica g;
        cria_gram_closure_1(g);
        gramaticaEstendida(g);

        std::set<std::shared_ptr<Item>> conjI0;
        std::set<std::shared_ptr<Item>> out;
        cria_goto_manual_1(conjI0, out);

        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>("A");
        std::set<std::shared_ptr<Item>> conj_goto;
        funcaoGoto(conjI0, sym, g, conj_goto);

        CHECK(conjuntosIguais(out,conj_goto));
    }
    SUBCASE("Exemplo GeeksForGeeks: caso .aA"){
        Gramatica g;
        cria_gram_closure_1(g);
        gramaticaEstendida(g);

        std::set<std::shared_ptr<Item>> conjI0;
        std::set<std::shared_ptr<Item>> out;
        cria_goto_manual_2(conjI0, out);

        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("a");
        std::set<std::shared_ptr<Item>> conj_goto;
        funcaoGoto(conjI0, sym, g, conj_goto);
        
        // std::cout << "CONJ_GOTO:" << std::endl;
        // for (auto elm0 : conj_goto){
        //     std::cout << "\t" << *elm0 << std::endl;
        // }
        // std::cout << "OUT:" << std::endl;
        // for (auto elm0 : out){
        //     std::cout << "\t" << *elm0 << std::endl;
        // }
        CHECK(conjuntosIguais(out,conj_goto));
    }
}

TEST_CASE("Utils: conjuntosItens"){
    std::set<std::set<std::shared_ptr<Item>>> out;
    out.clear();
    cria_sets_manual(out);

    Gramatica g;
    cria_gram_goto(g);
    gramaticaEstendida(g);

    ConjuntoItens c;
    conjuntosItens(c, g);

    CHECK(c.qtdConjuntos() == out.size());

    bool possuiConj = false;
    for (auto conj: out){
        possuiConj = false;
        auto it = c.find(conj);
        if (it != c.end()){
            possuiConj = true;
        }else{
            std::cout << "Conjunto Ausente:" << std::endl;
            for (auto elm0 : conj){
                std::cout << "\t" << *elm0 << std::endl;
            }
        }
        CHECK(possuiConj == true);
    }
}


TEST_CASE("Utils: tabActionGoto"){
    Gramatica g;
    cria_gram_goto(g);
    gramaticaEstendida(g);

    TabelaAction tabAction;
    TabelaGoto tabGoto;

    tabActionGoto(tabAction, tabGoto, g, true);
    // print_action_goto_manual(tabAction, tabGoto);

    std::cout << "tabActionGoto: !!!!CONFERÊNCIA MANUAL!!!! (ok: 30/12/2020 13:52)" << std::endl;
}