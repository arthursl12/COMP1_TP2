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

};

#endif /* PROD_H */
