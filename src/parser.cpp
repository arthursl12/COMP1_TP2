#include "parser.h"
#include "tabelas.h"

#include <stack>
#include <iostream>

bool parser(std::vector<std::shared_ptr<Symbol>>& entrada, Gramatica& g){
    // Estende a gramática e cria as tabelas
    gramaticaEstendida(g);
    TabelaAction tabAction;
    TabelaGoto tabGoto;
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
        if (it == tabAction[atualEstado]->end()){ 
            std::cout << "Erro de Sintaxe" << std::endl;
            return false;
        }
        
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
                pEstados.pop();
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
            if (it == tabGoto[t]->end()){ 
                std::cout << "Erro de Sintaxe (GOTO)" << std::endl;
                return false; 
            }
            int idxGoto = it->second;
            pEstados.push(idxGoto);
        }else if (it->second->getTipo() == "Accept"){
            std::cout << "Programa Aceito" << std::endl;
            break;
        }else{
            std::cout << "Erro de Sintaxe Geral" << std::endl;
            return false;
        }
    }
    return true;
}