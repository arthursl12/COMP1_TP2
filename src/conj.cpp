#include "conj.h"


ConjuntoItens::ConjuntoItens(){
    conjs.clear();
    std::shared_ptr<Elemento> el0 = std::make_shared<Elemento>();
    el0->label = "I" + std::to_string(conjs.size());
    std::shared_ptr<Item> it0 = std::make_shared<Item>();
    el0->conj_item.insert(it0);
    conjs.insert(el0);
}

std::set<std::shared_ptr<Elemento>>::iterator ConjuntoItens::begin(){
    return conjs.begin();
}
std::set<std::shared_ptr<Elemento>>::iterator ConjuntoItens::find(
    std::set<std::shared_ptr<Item>>& conj_item)
{
    auto it = conjs.begin();
    for (; it != conjs.end(); it++){
        if (  (**it).conj_item == conj_item  ){
            return it;
        }       
    }
    return conjs.end();
}
std::set<std::shared_ptr<Elemento>>::iterator ConjuntoItens::end(){
    return conjs.end();
}

void ConjuntoItens::insert(std::set<std::shared_ptr<Item>>& conj_item){
    if (conjs.size() == 1){
        Item el = (**((*conjs.begin())->conj_item.begin()));
        if (el == Item()){
            conjs.clear();
        }
    }

    std::shared_ptr<Elemento> el0 = std::make_shared<Elemento>();
    el0->label = "I" + std::to_string(conjs.size());
    el0->conj_item = conj_item;
    conjs.insert(el0);
}

int ConjuntoItens::qtdConjuntos(){
    return conjs.size();
}

void ConjuntoItens::getLabels(std::set<std::string>& out){
    for (auto elem: conjs){
        out.insert(elem->label);
    }
}
