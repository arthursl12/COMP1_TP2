#include "utils.h"
#include "item.h"
#include <iostream>
#include <stack>

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

                auto find = conjs.find(out);
                if (find == conjs.end() && out.size() > 0){
                    conjs.insert(out);
                    adicionou = true;
                }
            }
            
        }
    }
}

void inicializaTabelas(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>>& tabGoto,
    int qtdEstados,
    std::set<NaoTerminal>& nts,
    std::set<Terminal>& tts
){
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
}

void actionTerminalPonto(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    Elemento& elm,
    int idx,
    Cadeia& cad,
    ConjuntoItens& its,
    Gramatica& g
){
    std::shared_ptr<Symbol> ponto = std::make_shared<Terminal>(".");
    auto it_ponto = cad.find(ponto);
    if (it_ponto != cad.end()){
        auto it_dps_ponto = it_ponto + 1; 
        if (it_dps_ponto != cad.end() && (**it_dps_ponto).isTerminal()){
            std::shared_ptr<Terminal> ptr_a = \
                std::dynamic_pointer_cast<Terminal>(*it_dps_ponto);

            // Computa GOTO(Ii,a)
            std::set<std::shared_ptr<Item>> gotoIi;
            std::shared_ptr<Symbol> sym = \
                            std::make_shared<Terminal>(*ptr_a);

            funcaoGoto(elm.conj_item, sym, g, gotoIi);

            // Se GOTO(Ii,a) = Ij entao ACTION[i,a] = shift j
            if (gotoIi.size() > 0){
                auto it = its.find(gotoIi);
                if (it == its.end())
                    throw "Goto não encontrado (shift)";
                int shiftIdx = (**it).idx;


                // ACTION[i,a] = shift j
                auto ptr_vec = tabAction[idx];
                auto vec = *ptr_vec;
                int k = 0;
                for(; k < (int)ptr_vec->size(); k++){
                    if (ptr_vec->at(k).first == *ptr_a){
                        break;
                    }
                }
                std::pair<Terminal,std::shared_ptr<Acao>> newPair = 
                    std::make_pair<Terminal,std::shared_ptr<Acao>>(
                        Terminal(*ptr_a),
                        std::make_shared<Shift>(shiftIdx)
                    );
                ptr_vec->at(k) = newPair;
                vec = *ptr_vec;
            }
        }
    }
}

void actionReduce(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    Cadeia& cad,
    Item& item,
    int idx,
    Gramatica& g
){
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
}

void actionAccept(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    Item& item,
    int idx,
    Gramatica& g
){
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
}

void preencheTabelaGoto(
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>>& tabGoto,
    std::set<NaoTerminal>& nts,
    Gramatica& g,
    Elemento& elm,
    int idx,
    ConjuntoItens& its
){
    for(NaoTerminal nt: nts){
        // Para todo não-terminal
        std::set<std::shared_ptr<Item>> gotoIi;
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>(nt);

        funcaoGoto(elm.conj_item, sym, g, gotoIi);

        // Se GOTO(Ii,A) = Ij entao GOTO(i,A) = j
        if (gotoIi.size() > 0){
            auto it = its.find(gotoIi);
            if (it == its.end())
                throw "Goto não encontrado (goto)";
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
    inicializaTabelas(tabAction, tabGoto, qtdEstados, nts, tts);

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
    // Itera por cada estado
    for(auto it_estado = its.begin(); it_estado != its.end(); it_estado++){
        Elemento elm = **it_estado;
        int idx = elm.idx;
        std::set<std::shared_ptr<Item>> conj = elm.conj_item;

        // Por cada item do estado
        for(std::shared_ptr<Item> ptr_item: conj){
            Item item = *ptr_item;
            Cadeia cad = item.getCadeia();

            // ACTION
            // Caso: terminal depois do ponto
            actionTerminalPonto(tabAction, elm, idx, cad, its, g);
            // Caso: ponto no fim -> reduce
            actionReduce(tabAction, cad, item, idx, g);
            // Caso: ponto após inicial -> accept
            actionAccept(tabAction, item, idx, g);
            
            // GOTO
            preencheTabelaGoto(tabGoto, nts, g, elm, idx, its);
        }
    }
}

bool parser(std::vector<std::shared_ptr<Symbol>>& entrada, Gramatica& g){
    // Estende a gramática e cria as tabelas
    gramaticaEstendida(g);
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>> tabAction;
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>> tabGoto;
    tabActionGoto(tabAction, tabGoto, g);

    // Cria as pilhas
    std::stack<std::shared_ptr<Symbol>> pSym;
    std::stack<int> pEstados;
    pEstados.push(0);   // Começa do estado 0

    // Coloca o marcador de fim na entrada
    std::shared_ptr<Symbol> fim = std::make_shared<Terminal>("$");
    entrada.push_back(fim);

    auto sym = entrada.begin();
    while(1){
        int atualEstado = pEstados.top();

        // Acha a ação com base no estado e na entrada
        auto it = tabAction[atualEstado]->begin();
        for(; it != tabAction[atualEstado]->end(); it++){
            if (it->first == **sym){ break; }
        }
        if (it == tabAction[atualEstado]->end()){ throw "Erro de Sintaxe";}
        
        // Lógica Principal
        if (it->second->getTipo() == "Shift"){
            std::shared_ptr<Shift> sft = \
                             std::dynamic_pointer_cast<Shift>(it->second);
            int next = sft->getNextIdx();
            pEstados.push(next);
            pSym.push(*sym);
            sym++;
        }else if (it->second->getTipo() == "Reduce"){
            std::shared_ptr<Reduce> red = \
                             std::dynamic_pointer_cast<Reduce>(it->second);
            int idxProd = red->getProdIdx();

            Cadeia cad = g.getCadeia(idxProd);
            for(int i = 0; i < cad.qtdSimbolos(); i++){
                pSym.pop();
            }
            int t = pEstados.top();

            std::shared_ptr<Symbol> lhs = \
                            std::make_shared<NaoTerminal>(g.getLhs(idxProd));
            pSym.push(lhs);

            // Acha o GOTO(t,A), sendo A = lhs
            auto it = tabGoto[t]->begin();
            for(; it != tabGoto[t]->end(); it++){
                if (it->first == *lhs){ break; }
            }
            if (it == tabGoto[t]->end()){ throw "Erro de Sintaxe (GOTO)"; }
            int idxGoto = it->second;
            pEstados.push(idxGoto);
        }else if (it->second->getTipo() == "Accept"){
            std::cout << "Aceito" << std::endl;
            break;
        }else{
            throw "Erro de Sintaxe Geral";
            return false;
        }
    }
    return true;
}

