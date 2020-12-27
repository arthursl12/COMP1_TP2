#include "utils.h"
#include "item.h"

void gramaticaEstendida(Gramatica& g){
    std::vector<std::shared_ptr<Producao>> prods = g.prods;
    NaoTerminal antigoS = prods[0]->label();
    
    std::vector<std::shared_ptr<Symbol>> seq;
    seq.push_back(std::make_shared<NaoTerminal>(antigoS));
    std::shared_ptr<Cadeia> cad = std::make_shared<Cadeia>(seq);
    std::vector<std::shared_ptr<Cadeia>> v;
    v.push_back(cad);

    std::shared_ptr<Producao> newS = \
        std::make_shared<Producao>(NaoTerminal("S\'"),v);
    prods.insert(prods.begin(), newS);
    g = Gramatica(prods);
}

void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g){
    for (auto iter = conj.begin(); iter != conj.end(); iter++){
        Cadeia cad = (**iter).getCadeia();
        std::shared_ptr<Symbol> ponto = std::make_shared<Terminal>(".");
        auto iter1 = cad.find(ponto);
        if (!(**(iter1++)).isTerminal()){
            // Se o que vier depois do ponto não for um terminal
            
            // Explicita o não-terminal
            std::shared_ptr<Symbol> temp_symbol = *(iter1++);
            std::shared_ptr<NaoTerminal> nt = \
                        std::dynamic_pointer_cast<NaoTerminal>(temp_symbol);

            // Acha as produções desse não terminal na gramática
            throw "Finalizar função";
        }
    }
}