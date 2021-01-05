#ifndef TABELAS_H
#define TABELAS_H

#include "utils.h"

void inicializaTabelas(TabelaAction& tabAction, TabelaGoto& tabGoto,
                       int qtdEstados, 
                       std::set<NaoTerminal>& nts, std::set<Terminal>& tts);


void actionTerminalPonto(TabelaAction& tabAction, Elemento& elm, int idx,
                         Cadeia& cad, ConjuntoItens& its, Gramatica& g);
void actionAccept(TabelaAction& tabAction, Item& item, int idx, Gramatica& g);
void actionReduce(TabelaAction& tabAction, Cadeia& cad, Item& item,
                  int idx, Gramatica& g);
void preencheTabelaGoto(TabelaGoto& tabGoto, std::set<NaoTerminal>& nts,
                        Gramatica& g, Elemento& elm, 
                        int idx, ConjuntoItens& its);

void printEstados(ConjuntoItens& its);
void printActionGoto(TabelaAction& tabAction,TabelaGoto& tabGoto);
void tabActionGoto(TabelaAction& tabAction, TabelaGoto& tabGoto, 
                                    Gramatica& g, bool apenas_imprimir = false);

#endif /* TABELAS_H */