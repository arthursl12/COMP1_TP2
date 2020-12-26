#include "gram.h"
#include "prod.h"

#include <ostream>
#include <iostream>
#include <set>
#include <memory>


Gramatica::Gramatica(){
    prods.clear();
    prods.push_back(std::make_shared<Producao>());
    prods[0]->setInicial();
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
    prods[0]->setInicial();
    for (auto it = (prods.begin()+1); it != prods.end(); it++){
        (*it)->removeInicial();
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
        std::set<Terminal> out2 = out1;
        if (out2.find(Terminal("")) != out2.end()){
            out2.erase(out2.find(Terminal("")));
        }
        out = getUnion(out, out2);
        
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
            std::set<Terminal> out2 = out1;
            if (out2.find(Terminal("")) != out2.end()){
                out2.erase(out2.find(Terminal("")));
            }
            out = getUnion(out, out2);
            
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

void Gramatica::follow(std::shared_ptr<NaoTerminal>& sym, std::set<Terminal>& out){
    // Verifica se é o inicial, se sim, adiciona $ ao FOLLOW
    int i = 0;
    for(i = 0; i < (int)prods.size(); i++){
        if ((*sym) == prods[i]->label()){
            break;
        }
    }
    if (prods[i]->isInicial()){
        out.insert(Terminal("$"));
    }

    //Fluxo normal: procura em quais produções o símbolo é utilizado
    for(i = 0; i < (int)prods.size(); i++){
        if (prods[i]->label() == *sym){
            continue;
        }
        for (int j = 0; j < prods[i]->qtdCadeias(); j++){
            Cadeia cad = (*prods[i])[j];
            auto it = cad.find(sym);
            while(it != cad.end()){
                // Caso produção A -> pBq: adiciona FIRST(q) a FOLLOW(B) 
                // (exceto o vazio)
                if ((it+1) != cad.end()){
                    auto it2 = it+1;
                    // Existe um símbolo à direita
                    std::set<Terminal> out1;
                    first(*it2, out1);
                    
                    // Adiciona tudo exceto o vazio
                    std::set<Terminal> out2 = out1;
                    if (out2.find(Terminal("")) != out2.end()){
                        out2.erase(out2.find(Terminal("")));
                    }
                    out = getUnion(out, out2);

                    if (out1.find(Terminal("")) == out1.end()){
                        it = cad.find(sym, it);
                        continue;
                    }
                    it2++;
                    // Enquanto FIRST(Yi) possuir (vazio),
                    // adicione FIRST(Y+1) (sem o vazio) a FOLLOW(B)
                    while(  !(out1.find(Terminal("")) == out1.end()) 
                          && it2 != cad.end()){
                        
                        out1.clear();
                        first(*it2, out1);
                        std::set<Terminal> out2 = out1;
                        if (out2.find(Terminal("")) != out2.end()){
                            out2.erase(out2.find(Terminal("")));
                        }
                        out = getUnion(out, out2);
                        it2++;
                    }
                    if (it2 == cad.end() && !(out1.find(Terminal("")) == out1.end())){
                        // Todos possuem vazio: adicione o FOLLOW(A) também
                        // Ou temos o caso A -> pBq (com q tendo vazio)
                        out1.clear();
                        std::shared_ptr<NaoTerminal> prod_label = \
                            std::make_shared<NaoTerminal>(prods[i]->label());
                        follow(prod_label, out1);
                        out = getUnion(out, out1);
                    }
                }

                // Caso produção A -> pBq (com q vazio) (incluída acima)
                
                // Caso produção A -> pB: adiciona FOLLOW(A) a FOLLOW(B)
                if ((it+1) == cad.end()){
                    std::set<Terminal> out1;
                    std::shared_ptr<NaoTerminal> prod_label = \
                            std::make_shared<NaoTerminal>(prods[i]->label());
                    follow(prod_label, out1);
                    out = getUnion(out, out1);
                }
                // Controle Loop
                it = cad.find(sym, it);
            }
        }
    }


}