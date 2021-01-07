#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "action.h"
#include "gram.h"
#include "conj.h"

typedef std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>> TabelaAction;
typedef std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>> TabelaGoto;

void gramaticaEstendida(Gramatica& g);
void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g);
void funcaoGoto(std::set<std::shared_ptr<Item>>& in, 
                std::shared_ptr<Symbol>& sym, 
                Gramatica& g,
                std::set<std::shared_ptr<Item>>& out);
void conjuntosItens(ConjuntoItens& conjs, Gramatica& g);
void inputFile(std::vector<std::string>& programas, std::string filename);
void inputId(std::string& out, std::string idName);

#endif /* UTILS_H */
