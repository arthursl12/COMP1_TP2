#ifndef CADEIA_H
#define CADEIA_H

#include "symbol.h"

#include <ostream>
#include <vector>
#include <memory>

class Cadeia{
    protected:
        std::vector<std::shared_ptr<Symbol>> seq;
    public:
        Cadeia();
        Cadeia(std::shared_ptr<Symbol>& s);
        Cadeia(std::vector<std::shared_ptr<Symbol>>& _seq);
        Symbol& operator[](int idx);
        bool operator==(Cadeia const& rhs) const;
        friend std::ostream& operator<< (std::ostream &out, const Cadeia &c); 
};

#endif /* CADEIA_H */
