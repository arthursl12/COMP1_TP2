#include "gram.h"
#include "prod.h"

#include <ostream>
#include <set>
#include <memory>


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

void Gramatica::firstString(std::shared_ptr<Producao> p, std::set<Terminal>& out){
    // Para todas as produções do tipo X = Y1 Y2 ... Yn
    for (int i = 0; i < p->qtdCadeias(); i++){
        Cadeia cad = (*p)[i];
        std::shared_ptr<Symbol> vazio = std::make_shared<Terminal>("");
        if (cad == Cadeia(vazio)){
            continue;
        }

        // FIRST(X) = FIRST(Y1)
        std::set<Terminal> out1;
        std::shared_ptr<Symbol> cadk;
        if (cad[0].isTerminal()){
            Terminal& t = dynamic_cast<Terminal&>(cad[0]);
            cadk = std::make_shared<Terminal>(t);
        }else{
            NaoTerminal& nt = dynamic_cast<NaoTerminal&>(cad[0]);
            cadk = std::make_shared<NaoTerminal>(nt);
        }
        first(cadk, out1);
        out = getUnion(out, out1);

        int j = 1;
        // Enquanto FIRST(Yi) possuir (vazio),
        // adicione FIRST(Y+1) a FIRST(X)
        while(  !(out1.find(Terminal("")) == out1.end())  ){
            out1.clear();
            if (cad[j].isTerminal()){
                Terminal& t = dynamic_cast<Terminal&>(cad[j]);
                cadk = std::make_shared<Terminal>(t);
            }else{
                NaoTerminal& nt = dynamic_cast<NaoTerminal&>(cad[j]);
                cadk = std::make_shared<NaoTerminal>(nt);
            }
            first(cadk, out1);
            out = getUnion(out, out1);
            
            j++;
            if (j == cad.qtdSimbolos()){
                out.insert(Terminal(""));
                break;
            }
        }
    }
}

void Gramatica::first(std::shared_ptr<Symbol>& sym, std::set<Terminal>& out){
    if (sym->isTerminal()){
        // FIRST de terminal só possui ele
        std::shared_ptr<Terminal> t = std::dynamic_pointer_cast<Terminal>(sym);
        out.insert(*t);
    }else{
        std::shared_ptr<NaoTerminal> nt = \
                    std::dynamic_pointer_cast<NaoTerminal>(sym);

        // Acha as produções do não terminal
        std::shared_ptr<Producao> p;
        for (auto it = prods.begin(); it != prods.end(); it++){
            std::shared_ptr<Producao> p_it = *it;
            if (p_it->label() == *nt){
                p = p_it;
            }
        }

        // Se houver produção X->(vazio) adicione (vazio) ao conjunto
        for (int i = 0; i < p->qtdCadeias(); i++){
            Cadeia cad = (*p)[i];
            std::shared_ptr<Symbol> vazio = std::make_shared<Terminal>("");
            if (cad == Cadeia(vazio)){
                out.insert(Terminal(""));
                break;
            }
        }

        firstString(p, out);
    }
}