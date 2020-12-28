#ifndef UTILS_H
#define UTILS_H

#include "gram.h"

void gramaticaEstendida(Gramatica& g);
void itemL0(Producao& p);
void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g);
void funcaoGoto(std::set<std::shared_ptr<Item>>& in, 
                std::shared_ptr<Symbol>& sym, 
                Gramatica& g,
                std::set<std::shared_ptr<Item>>& out);

#endif /* UTILS_H */
