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

bool possuiItemNaoTerminal(std::set<std::shared_ptr<Item>>& conj, 
                           std::shared_ptr<NaoTerminal> nt)
{
    for (auto elem : conj){
        if (elem->label() == *nt){
            return true;
        }
    }
    return false;
}   

void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g){
    bool adicionou = true;
    while(adicionou){
        for (auto iter = conj.begin(); iter != conj.end(); iter++){
            Cadeia cad = (**iter).getCadeia();
            std::shared_ptr<Symbol> ponto = std::make_shared<Terminal>(".");
            auto iter1 = cad.find(ponto);
            iter1++;
            std::shared_ptr<Symbol> prox = *(iter1++);

            // Explicita o não-terminal
            std::shared_ptr<NaoTerminal> nt = \
                            std::dynamic_pointer_cast<NaoTerminal>(prox);
            
            adicionou = false;
            if (  !(   (*prox).isTerminal()  )  &&   !possuiItemNaoTerminal(conj,nt) ){
                // Se o que vier depois do ponto não for um terminal
                // E a produção daquele não-terminal ainda não foi adicionada
            
                // Acha as produções desse não terminal na gramática
                for(auto prod : g.prods){
                    if (prod->label() == *nt){
                        for (int i = 0; i < prod->qtdCadeias(); i++){
                            // Cria um item para cada cadeia dessa produção
                            std::shared_ptr<Item> item = \
                                            std::make_shared<Item>((*prod),i);
                            conj.insert(item);
                            adicionou = true;
                        }
                    }
                }
            }
        }
    }
    
}