#include "tabelas.h"
#include <iomanip>
#include <iostream>

void inicializaTabelas(
    TabelaAction& tabAction,
    TabelaGoto& tabGoto,
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
    TabelaAction& tabAction,
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
    TabelaAction& tabAction,
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
                if (actionIdx == 0){
                    // Reduzir a produção inicial não pode
                    continue;
                }
                // ACTION[i,a] = reduce
                auto ptr_vec = tabAction[idx];
                auto vec = *ptr_vec;
                int k = 0;
                for(; k < (int)ptr_vec->size(); k++){
                    if (ptr_vec->at(k).first == a){
                        break;
                    }
                }
                std::shared_ptr<Acao> act = std::make_shared<Reduce>(actionIdx);
                std::pair<Terminal,std::shared_ptr<Acao>> newPair = 
                    std::make_pair<Terminal,std::shared_ptr<Acao>&>(
                        Terminal(a),
                        act
                    );
                ptr_vec->at(k) = newPair;
                vec = *ptr_vec;
            }
        }
    }
}

void actionAccept(
    TabelaAction& tabAction,
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
    TabelaGoto& tabGoto,
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

void printEstados(ConjuntoItens& its){
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
}


void printActionGoto(TabelaAction& tabAction,TabelaGoto& tabGoto){   
    int SPC = 7;
    std::cout << "======ACTION======" << std::endl;
    auto linha0 = tabAction.begin();
    std::cout << "|" << std::setw(SPC) << "I" << std::setw(SPC);
    for (auto pares0: **linha0){
        std::cout << "|" << std::setw(SPC) << pares0.first << std::setw(SPC);
    }
    std::cout << "|" << std::endl;

    int i = 0;
    for(auto linha: tabAction){
        std::cout << "|" << std::setw(SPC) << "I" + std::to_string(i) << std::setw(SPC);
        for(auto par: *linha){
            if (par.second->getTipo() == "Error"){
                std::cout << "|" << std::setw(SPC) << "" << std::setw(SPC);
            }else if (par.second->getTipo() == "Shift"){
                std::shared_ptr<Shift> sft = \
                            std::dynamic_pointer_cast<Shift>(par.second);
                std::cout << "|" << std::setw(SPC) << *sft << std::setw(SPC-3);
            }else if (par.second->getTipo() == "Reduce"){
                std::shared_ptr<Reduce> red = \
                            std::dynamic_pointer_cast<Reduce>(par.second);
                std::cout << "|" << std::setw(SPC) << *red << std::setw(SPC-3);
            }else{
                std::cout << "|" << std::setw(SPC) << par.second->getTipo() << std::setw(SPC);
            }
        }
        i++;
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "======GOTO======" << std::endl;
    auto linha1 = tabGoto.begin();
    std::cout << "|" << std::setw(SPC) << "I" << std::setw(SPC);
    for (auto pares0: **linha1){
        std::cout << "|" << std::setw(SPC-1) << pares0.first << std::setw(SPC-1);
    }
    std::cout << "|" << std::endl;

    i = 0;
    for(auto linha: tabGoto){
        std::cout << "|" << std::setw(SPC) << "I" + std::to_string(i) << std::setw(SPC);
        for(auto par: *linha){
            if (par.second == -1){
                std::cout << "|" << std::setw(SPC) << "" << std::setw(SPC);
            }else{
                std::cout << "|" << std::setw(SPC) << par.second << std::setw(SPC);
            }
            
        }
        i++;
        std::cout << "|" << std::endl;
    }
}

void tabActionGoto(TabelaAction& tabAction, TabelaGoto& tabGoto, 
                   Gramatica& g, bool apenas_imprimir)
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

    // Imprimir tabelas e estados se requisitado
    if (apenas_imprimir){
        printEstados(its);
        printActionGoto(tabAction, tabGoto);
    }
}