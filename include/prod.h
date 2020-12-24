#ifndef PROD_H
#define PROD_H

#include "symbol.h"

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
};

#endif /* PROD_H */
