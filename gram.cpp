#include "gram.h"

#include <ostream>

Gramatica::Gramatica(){
    prods.clear();
    prods.push_back(std::make_shared<Producao>());
}

Gramatica::Gramatica(std::vector<std::shared_ptr<Producao>>& _prods){
    prods.clear();
    for (auto it = _prods.begin(); it != _prods.end(); it++){
        prods.push_back(*it);
    }
}

std::ostream& operator<< (std::ostream &out, const Gramatica& g){
    out << "========================" << std::endl;
    out << "Gramática: " << std::endl;
    for (auto it = g.prods.begin(); it != g.prods.end(); it++){
        out << (**it) << std::endl;
    }
    out << "========================" << std::endl;
    return out;
}

void conjuntoTerminais(std::set<Terminal>& out){
    
}

void conjuntoNaoTerminais(std::set<NaoTerminal>& out){

}