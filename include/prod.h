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
        bool inicial;
    public:
        Producao();
        Producao(NaoTerminal _lhs, std::vector<std::shared_ptr<Cadeia>> _rhs);
        Cadeia& operator[](int idx);
        bool operator==(Producao const& oth) const;
        NaoTerminal label(); 
        friend std::ostream& operator<< (std::ostream &out, const Producao& p); 
        void conjuntoTerminais(std::set<Terminal>& out);
        void conjuntoNaoTerminais(std::set<NaoTerminal>& out);

        int qtdCadeias();

        void setInicial();
        void removeInicial();
        bool isInicial();

        friend void itemL0(Producao& p);
};

template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b);

#endif /* PROD_H */
