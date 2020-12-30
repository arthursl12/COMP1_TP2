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

/*
Verifica se um conjunto de ponteiros de Item 'conj' possui pelo menos todas as 
produções do não-terminal 'nt' da gramática 'g'.
*/
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

/*
Função auxiliar de closure. Adiciona todas as produções do não-terminal 'nt'
em forma de item no conjunto de itens 'conj'
*/
void adicionaProducoes(std::set<std::shared_ptr<Item>>& conj,
                       std::shared_ptr<NaoTerminal>& nt, 
                       Gramatica& g, 
                       bool& adicionou)
{
    // Acha as produções desse não-terminal na gramática
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

void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g){
    bool adicionou = true;
    // Enquanto for possível adicionar conjuntos
    while(adicionou){
        adicionou = false;
        // Para cada conjunto
        for (auto iter = conj.begin(); iter != conj.end(); iter++){
            Cadeia cad = (**iter).getCadeia();
            std::shared_ptr<Symbol> ponto = std::make_shared<Terminal>(".");
            auto iter1 = cad.find(ponto);
            iter1++;
            if (iter1 == cad.end()){ continue;}
            std::shared_ptr<Symbol> prox = *(iter1++);

            // Continue se for terminal
            if (prox->isTerminal()){ continue;}

            // Explicita o não-terminal
            std::shared_ptr<NaoTerminal> nt = \
                            std::dynamic_pointer_cast<NaoTerminal>(prox);
            
            // Se o que vier depois do ponto não for um terminal (checado acima)
            // E todas as produções daquele não-terminal que ainda 
            // não foram adicionadas
            bool cond1 = possuiItemNaoTerminal(conj,nt,g);
            if ( !cond1 ){
                adicionaProducoes(conj, nt, g, adicionou);
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

void tabActionGoto(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>>& tabGoto,
    Gramatica& g)
{
    // Informações da gramática
    std::set<NaoTerminal> nts;
    std::set<Terminal> tts;
    g.conjuntoNaoTerminais(nts);
    nts.erase(NaoTerminal("S\'"));
    g.conjuntoTerminais(tts);
    tts.insert(Terminal("$"));

    // Cria conjunto de itens para a gramática
    ConjuntoItens its;
    conjuntosItens(its, g);
    int qtdEstados = its.qtdConjuntos();

    // Inicializa as tabelas
    tabAction.clear();
    tabGoto.clear();
    for(int i = 0; i < qtdEstados; i++){
        std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> linhaGoto;
        linhaGoto = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
        for(NaoTerminal nt: nts){
            if (nt == NaoTerminal("S\'")) { continue;}
            std::pair<NaoTerminal,int> parGoto = \
                            std::make_pair<NaoTerminal,int>(NaoTerminal(nt),-1);
            linhaGoto->push_back(parGoto);
        }
        tabGoto.push_back(linhaGoto);

        std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> linhaAction;
        linhaAction = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
        for(Terminal t: tts){
            std::shared_ptr<Acao> err = std::make_shared<Error>();
            std::pair<Terminal,std::shared_ptr<Acao>> parAction = \
                std::make_pair<Terminal,std::shared_ptr<Acao>>(
                    Terminal(t),std::make_shared<Error>()
                );
            linhaAction->push_back(parAction);
        }
        tabAction.push_back(linhaAction);
    }

    // DEBUG (print estados):
    for(auto it_estado = its.begin(); it_estado != its.end(); it_estado++){
        Elemento elm = **it_estado;
        std::set<std::shared_ptr<Item>> conj = elm.conj_item;
        std::cout << "Estado: " << elm.label << std::endl;
        
        for (std::shared_ptr<Item> ptr_item: conj){
            std::cout << "\t" << *ptr_item << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


    // Cria Action e Goto para cada estado
    int i = 0;
    for(auto it_estado = its.begin(); it_estado != its.end(); it_estado++){
        Elemento elm = **it_estado;
        int idx = elm.idx;
        std::set<std::shared_ptr<Item>> conj = elm.conj_item;

        for(std::shared_ptr<Item> ptr_item: conj){
            Item item = *ptr_item;
            Cadeia cad = item.getCadeia();

            // ACTION
            // Caso: ponto antes de terminal

            // Caso: ponto no fim -> reduce
            if (cad[cad.qtdSimbolos()-1] == Terminal(".")){
                NaoTerminal A = item.label();
                if ( !  (A == NaoTerminal("S\'")  )){
                    std::shared_ptr<NaoTerminal> ptr_A = \
                        std::make_shared<NaoTerminal>(A);
                    std::set<Terminal> followA;
                    g.follow(ptr_A, followA);

                    for(Terminal a: followA){
                        // TODO: idx da produção
                        int actionIdx = g.getProdIndex(A, cad);
                        if (actionIdx == -1)
                            throw "Problema na busca pela produção";
                        // ACTION[i,a] = reduce
                        auto ptr_vec = tabAction[idx];
                        auto vec = *ptr_vec;
                        int k = 0;
                        for(; k < (int)ptr_vec->size(); k++){
                            if (ptr_vec->at(k).first == a){
                                break;
                            }
                        }
                        std::pair<Terminal,std::shared_ptr<Acao>> newPair = 
                            std::make_pair<Terminal,std::shared_ptr<Acao>>(
                                Terminal(a),
                                std::make_shared<Reduce>(actionIdx)
                            );
                        ptr_vec->at(k) = newPair;
                        vec = *ptr_vec;
                    }
                }
            }

            // Caso: ponto após inicial -> accept
            Item reconhecido = Item(g.getInicial());
            reconhecido.avanca();
            if (item == reconhecido){
                auto ptr_vec = tabAction[idx];
                auto vec = *ptr_vec;
                int k = 0;
                for(; k < (int)ptr_vec->size(); k++){
                    if (ptr_vec->at(k).first == Terminal("$")){
                        break;
                    }
                }
                std::pair<Terminal,std::shared_ptr<Acao>> newPair = 
                    std::make_pair<Terminal,std::shared_ptr<Acao>>(
                        Terminal("$"),
                        std::make_shared<Accept>()
                    );
                ptr_vec->at(k) = newPair;
                vec = *ptr_vec;
            }

            // GOTO
            for(NaoTerminal nt: nts){
                // Para todo não-terminal
                std::set<std::shared_ptr<Item>> gotoIi;
                std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>(nt);

                funcaoGoto(elm.conj_item, sym, g, gotoIi);

                // Se GOTO(Ii,A) = Ij entao GOTO(i,A) = j
                if (gotoIi.size() > 0){
                    auto it = its.find(gotoIi);
                    if (it == its.end())
                        throw "Goto não encontrado";
                    int gotoIdx = (**it).idx;

                    // Coloca GOTO(i,A) = j na tabela
                    auto ptr_vec = tabGoto[idx];
                    auto vec = *ptr_vec;
                    int k = 0;
                    for(; k < (int)ptr_vec->size(); k++){
                        if (ptr_vec->at(k).first == nt){
                            break;
                        }
                    }
                    std::pair<NaoTerminal,int> newPair = \
                        std::make_pair<NaoTerminal,int&>(NaoTerminal(nt),gotoIdx);
                    ptr_vec->at(k) = newPair;
                    vec = *ptr_vec;
                }
            }
        }

    }
}
