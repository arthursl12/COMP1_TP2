#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "action.h"
#include "gram.h"
#include "conj.h"

typedef std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>> TabelaAction;
typedef std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>> TabelaGoto;

void gramaticaEstendida(Gramatica& g);
void itemL0(Producao& p);
void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g);
void funcaoGoto(std::set<std::shared_ptr<Item>>& in, 
                std::shared_ptr<Symbol>& sym, 
                Gramatica& g,
                std::set<std::shared_ptr<Item>>& out);
void conjuntosItens(ConjuntoItens& conjs, Gramatica& g);


// Cria uma lista das regras (separado por cadeia)
void tabActionGoto(TabelaAction& tabAction, TabelaGoto& tabGoto, Gramatica& g);
bool parser(std::vector<std::shared_ptr<Symbol>>& entrada, Gramatica& g);



#endif /* UTILS_H */
