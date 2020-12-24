#include "gram.h"
#include "prod.h"

#include <ostream>
#include <set>


Gramatica::Gramatica(){
    prods.clear();
    prods.push_back(std::make_shared<Producao>());
}

void Gramatica::encontraNaoTerminais(
    std::set<NaoTerminal>& usados, std::set<NaoTerminal>& inicios)
{
    usados.clear();
    inicios.clear();
    for (auto it = prods.begin(); it != prods.end(); it++){
        std::set<NaoTerminal> temp1;
        (**it).conjuntoNaoTerminais(temp1);
        usados = getUnion(usados, temp1);
        inicios.insert((**it).label());
    }
}

/*
Verifica a integridade: não-terminais usados nas produções devem possuir uma
produção
*/
void Gramatica::verificaIntegridade(){
    std::set<NaoTerminal> usados;
    std::set<NaoTerminal> inicios;
    encontraNaoTerminais(usados, inicios);
    for (auto it = usados.begin(); it != usados.end(); it++){
        if (inicios.find(*it) == inicios.end()){
            throw "Não-terminal sem produção correspondente";
        }
    }
}

Gramatica::Gramatica(std::vector<std::shared_ptr<Producao>>& _prods){
    prods.clear();
    for (auto it = _prods.begin(); it != _prods.end(); it++){
        prods.push_back(*it);
    }

    verificaIntegridade();
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

void Gramatica::conjuntoTerminais(std::set<Terminal>& out){
    out.clear();
    for (auto it = prods.begin(); it != prods.end(); it++){
        std::set<Terminal> temp1;
        (**it).conjuntoTerminais(temp1);
        out = getUnion(out, temp1);
    }
}

void Gramatica::conjuntoNaoTerminais(std::set<NaoTerminal>& out){
    out.clear();
    std::set<NaoTerminal> usados;
    std::set<NaoTerminal> inicios;
    encontraNaoTerminais(usados, inicios);
    out = getUnion(usados, inicios);
}