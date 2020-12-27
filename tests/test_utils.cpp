#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "gram.h"
#include "item.h"

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


        for (auto elm0 : out){
            bool possui = false;
            for (auto elm1 : conjI0){
                if (*elm1 == *elm0){
                    possui = true;
                }
            }
            if (!possui){
                std::cout << *elm0 << std::endl;
            }
            CHECK(possui == true);
        }
        for (auto elm0 : conjI0){
            bool possui = false;
            for (auto elm1 : out){
                if (*elm1 == *elm0){
                    possui = true;
                }
            }
            if (!possui){
                std::cout << *elm0 << std::endl;
            }
            CHECK(possui == true);
        }
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

        
        for (auto elm0 : out){
            bool possui = false;
            for (auto elm1 : conjI0){
                if (*elm1 == *elm0){
                    possui = true;
                }
            }
            if (!possui){
                std::cout << *elm0 << std::endl;
            }
            CHECK(possui == true);
        }
        for (auto elm0 : conjI0){
            bool possui = false;
            for (auto elm1 : out){
                if (*elm1 == *elm0){
                    possui = true;
                }
            }
            if (!possui){
                std::cout << *elm0 << std::endl;
            }
            CHECK(possui == true);
        }
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
        for (auto elm0 : out){
            bool possui = false;
            for (auto elm1 : conjI0){
                if (*elm1 == *elm0){
                    possui = true;
                }
            }
            if (!possui){
                std::cout << *elm0 << std::endl;
            }
            CHECK(possui == true);
        }
        for (auto elm0 : conjI0){
            bool possui = false;
            for (auto elm1 : out){
                if (*elm1 == *elm0){
                    possui = true;
                }
            }
            if (!possui){
                std::cout << *elm0 << std::endl;
            }
            CHECK(possui == true);
        }
    }
}
