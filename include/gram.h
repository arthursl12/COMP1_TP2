#ifndef GRAM_H
#define GRAM_H

#include "prod.h"

#include <vector>
#include <memory>
#include <ostream>

class Gramatica{
    protected:
        std::vector<std::shared_ptr<Producao>> prods;
    public:
        Gramatica();
        Gramatica(std::vector<std::shared_ptr<Producao>>& _prods);
        friend std::ostream& operator<< (std::ostream &out, const Gramatica& g);

};

#endif /* GRAM_H */
