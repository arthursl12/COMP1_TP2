#include "conj.h"
#include <algorithm>

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
    std::set<std::shared_ptr<Item>>& conj_ptr_item)
{   
    std::vector<Item> in_itens;
    for (auto item: conj_ptr_item){
        in_itens.push_back(*item);
    }

    auto it = conjs.begin();
    // Para cada conjunto 
    for (; it != conjs.end(); it++){
        if ((**it).conj_item.size() != in_itens.size()){ continue; }

        bool possuiTodos = true;
        for (auto item_ptr: (**it).conj_item){
            auto find = std::find(in_itens.begin(), in_itens.end(), (*item_ptr));
            // auto find = in_itens.find(*item_ptr);
            if (find == in_itens.end()){
                possuiTodos = false;
                break;
            }
        }
        if (possuiTodos){
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
