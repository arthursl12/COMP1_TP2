#include "utils.h"
#include "item.h"
#include <iostream>

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
        if (itensComNt >= qtdCadeias){
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
        adicionou = false;
        for (auto iter = conj.begin(); iter != conj.end(); iter++){
            Cadeia cad = (**iter).getCadeia();
            std::shared_ptr<Symbol> ponto = std::make_shared<Terminal>(".");
            auto iter1 = cad.find(ponto);
            iter1++;
            if (iter1 == cad.end()){
                continue;
            }
            std::shared_ptr<Symbol> prox = *(iter1++);
            if (prox->isTerminal()){
                continue;
            }

            // Explicita o não-terminal
            std::shared_ptr<NaoTerminal> nt = \
                            std::dynamic_pointer_cast<NaoTerminal>(prox);
            
            
            bool cond1 = (*prox).isTerminal();
            bool cond2 = possuiItemNaoTerminal(conj,nt,g);
            if (  !(   cond1  )  &&   !cond2 ){
                // Se o que vier depois do ponto não for um terminal
                // E todas as produções daquele não-terminal que ainda 
                // não foram adicionadas
            
                // Acha as produções desse não-terminal na gramática
                for(auto prod : g.prods){
                    if (prod->label() == *nt){
                        for (int i = 0; i < prod->qtdCadeias(); i++){
                            // Cria um item para cada cadeia dessa produção
                            std::shared_ptr<Item> item = \
                                            std::make_shared<Item>((*prod),i);

                            // Ignora produções (cadeias) que já estão 
                            // representadas, mas com ponto em outro local
                            // bool jaPossuiItem = false;
                            // for (auto it: conj){
                            //     if (item->igualSemPonto(*it)){
                            //         jaPossuiItem = true;
                            //     }
                            // }
                            // if (!jaPossuiItem){
                            //     conj.insert(item);
                            //     adicionou = true;
                            // }
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

/*
Calcula os Conjuntos de Conjuntos de Itens (Estados do AF) para a gramática 
aumentada g
*/
void conjuntosItens(ConjuntoItens& conjs, Gramatica& g){
    // C = closure({S'->S})
    std::shared_ptr<Item> it0 = std::make_shared<Item>(g.getInicial());
    std::set<std::shared_ptr<Item>> closureS;
    closureS.insert(it0);
    closure(closureS, g);
    conjs.insert(closureS);

    // Determina o conjunto de símbolos da gramática (terminais e não-terminais)
    std::set<NaoTerminal> nts;
    g.conjuntoNaoTerminais(nts);
    std::set<Terminal> tts;
    g.conjuntoTerminais(tts);

    std::set<std::shared_ptr<Symbol>> symbs;
    for (NaoTerminal nt: nts){
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>(nt);
        symbs.insert(sym);
    }
    for (Terminal t: tts){
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(t);
        symbs.insert(sym);
    }

    // Loop principal
    bool adicionou = true;
    while(adicionou){
        adicionou = false;
        // Para cada conjunto
        for (auto it = conjs.begin(); it != conjs.end(); it++){
            Elemento el = (**it);
            std::set<std::shared_ptr<Item>> c1 = el.conj_item;
            // Para cada símbolo da gramática
            for (auto sym: symbs){
                std::set<std::shared_ptr<Item>> out;
                out.clear();

                funcaoGoto(c1, sym, g, out);
                // for (auto elem : c1){
                //     if (elem->deveAvancar(sym)){
                //         std::shared_ptr<Item> avancado = std::make_shared<Item>(*elem);
                //         avancado->avanca();
                        
                //         out.insert(avancado);
                //         closure(out, g);
                //     }
                // }
                auto find = conjs.find(out);
                if (find == conjs.end() && out.size() > 0){
                    conjs.insert(out);
                    // std::cout << "----Conjunto Adicionado----:" << std::endl;
                    // for (auto elm0 : out){
                    //     std::cout << "\t" << *elm0 << std::endl;
                    // }
                    // std::cout << std::endl;
                    adicionou = true;
                }
            }
            
        }
    }


}
