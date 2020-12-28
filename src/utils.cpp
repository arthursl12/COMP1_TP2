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
                           std::shared_ptr<NaoTerminal> nt,
                           Gramatica& g)
{
    // Verifica se possui alguma produção daquele não terminal
    bool possuiTerminal = false;
    for (auto elem : conj){
        if (elem->label() == *nt){
            possuiTerminal = true;
        }
    }
    if (possuiTerminal){
        // Verifica se todas as produções daquele terminal já foram adicionadas
        int qtdCadeias = g.qtdCadeias(nt);
        int itensComNt = 0;
        for (auto elem : conj){
            if (elem->label() == *nt){
                itensComNt++;
            }
        }
        if (qtdCadeias == itensComNt){
            return true;
        }else{
            return false;
        }    
    }else{
        return false;
    }
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

            if (  !(   (*prox).isTerminal()  )  &&   !possuiItemNaoTerminal(conj,nt,g) ){
                // Se o que vier depois do ponto não for um terminal
                // E todas as produções daquele não-terminal ainda 
                // não foram adicionadas
            
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

void funcaoGoto(std::set<std::shared_ptr<Item>>& in, 
                std::shared_ptr<Symbol>& sym, 
                Gramatica& g,
                std::set<std::shared_ptr<Item>>& out)
{
    for (auto elem : in){
        if (elem->deveAvancar(sym)){
            std::shared_ptr<Item> avancado = std::make_shared<Item>(*elem);
            avancado->avanca();
            
            out.insert(avancado);
            closure(out, g);
        }
    }
}