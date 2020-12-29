#ifndef GRAM_H
#define GRAM_H

#include "prod.h"
#include "symbol.h"
#include "item.h"

#include <vector>
#include <memory>
#include <set>
#include <ostream>

class Gramatica{
    protected:
        std::vector<std::shared_ptr<Producao>> prods;
    public:
        Gramatica();
        Gramatica(std::vector<std::shared_ptr<Producao>>& _prods);
        
        void conjuntoTerminais(std::set<Terminal>& out);
        void conjuntoNaoTerminais(std::set<NaoTerminal>& out);
        void encontraNaoTerminais(std::set<NaoTerminal>& usados, \
                                  std::set<NaoTerminal>& inicios);
        void verificaIntegridade();

        int qtdCadeias(std::shared_ptr<NaoTerminal> nt);
        Producao& getInicial();

        friend std::ostream& operator<< (std::ostream &out, const Gramatica& g);
        void firstString(std::shared_ptr<Producao> p, std::set<Terminal>& out);
        void first(std::shared_ptr<Symbol>& sym, std::set<Terminal>& out);
        void follow(std::shared_ptr<NaoTerminal>& sym, std::set<Terminal>& out);
        friend void gramaticaEstendida(Gramatica& g);
        friend void closure(std::set<std::shared_ptr<Item>>& conj, 
                            Gramatica& g);
        friend void adicionaProducoes(std::set<std::shared_ptr<Item>>& conj,
                                      std::shared_ptr<NaoTerminal>& nt, 
                                      Gramatica& g, bool& adicionou);



};

#endif /* GRAM_H */
