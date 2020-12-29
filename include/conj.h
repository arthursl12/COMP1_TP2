#ifndef CONJ_H
#define CONJ_H

#include "item.h"

#include <set>
#include <memory>

typedef struct Elemento{
    std::string label;
    int idx;
    std::set<std::shared_ptr<Item>> conj_item;
} Elemento;

class ConjuntoItens{
    protected:
        std::set<std::shared_ptr<Elemento>> conjs;
    public:
        ConjuntoItens();

        std::set<std::shared_ptr<Elemento>>::iterator 
            begin();
        std::set<std::shared_ptr<Elemento>>::iterator 
            find(std::set<std::shared_ptr<Item>>& conj_item);
        std::set<std::shared_ptr<Elemento>>::iterator 
            end();
        void insert(std::set<std::shared_ptr<Item>>& conj_item);
        int qtdConjuntos();

        void getLabels(std::set<std::string>& out);
        
};

#endif /* CONJ_H */
