#ifndef CADEIA_H
#define CADEIA_H

#include "symbol.h"

#include <ostream>
#include <vector>
#include <memory>
#include <set>

class Cadeia{
    protected:
        std::vector<std::shared_ptr<Symbol>> seq;
    public:
        Cadeia();
        Cadeia(std::shared_ptr<Symbol>& s);
        Cadeia(std::vector<std::shared_ptr<Symbol>>& _seq);
        Cadeia(Cadeia const& c);
        Symbol& operator[](int idx);
        bool operator==(Cadeia const& rhs) const;
        friend std::ostream& operator<< (std::ostream &out, const Cadeia &c); 
        void conjuntoTerminais(std::set<Terminal>& out);
        void conjuntoNaoTerminais(std::set<NaoTerminal>& out);
        int qtdSimbolos();

        std::vector<std::shared_ptr<Symbol>>::iterator \
            find(std::shared_ptr<Symbol>& nt);
        std::vector<std::shared_ptr<Symbol>>::iterator \
            find(std::shared_ptr<Symbol>& nt, \
                 std::vector<std::shared_ptr<Symbol>>::iterator& pos);
        std::vector<std::shared_ptr<Symbol>>::iterator \
            end();
        
        void itemLR0();
        void itemLR0(int pos);
        void avanca();
        bool deveAvancar(std::shared_ptr<Symbol>& sym);
        bool igualSemPonto(Cadeia const& oth) const;

};

#endif /* CADEIA_H */
