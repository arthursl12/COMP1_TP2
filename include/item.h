#ifndef ITEM_H
#define ITEM_H

#include "symbol.h"
#include "cadeia.h"
#include "prod.h"

#include <ostream>
#include <memory>

class Item{
    protected:
        NaoTerminal lhs;
        std::shared_ptr<Cadeia> rhs;
    public:
        Item();
        Item(Producao& p);
        Item(Producao& p, int pos);
        Item(Item const& oth);

        NaoTerminal label(); 
        Cadeia& getCadeia();

        bool operator==(Item const& oth) const;
        bool igualSemPonto(Item const& oth) const;
        
        void avanca();
        bool deveAvancar(std::shared_ptr<Symbol>& sym);

        friend std::ostream& operator<< (std::ostream &out, const Item& c); 

    

};

#endif /* ITEM_H */
