#ifndef PROD_H
#define PROD_H

#include "symbol.h"
#include "cadeia.h"
#include <memory>
#include <vector>

class Producao{
    protected:
        NaoTerminal lhs;
        std::vector<std::shared_ptr<Cadeia>> rhs;
    public:
        Producao();
        Producao(NaoTerminal _lhs, std::vector<std::shared_ptr<Cadeia>> _rhs);
        Cadeia& operator[](int idx);
        NaoTerminal label(); 
        friend std::ostream& operator<< (std::ostream &out, const Producao& p); 
        void conjuntoTerminais(std::set<Terminal>& out);
        void conjuntoNaoTerminais(std::set<NaoTerminal>& out);

};

#endif /* PROD_H */
