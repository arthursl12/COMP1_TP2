#include "cadeia.h"
#include "symbol.h"

#include <iostream>
#include <ostream>
#include <set>

Cadeia::Cadeia(){
    seq.clear();
    std::shared_ptr<Symbol> sym = std::make_shared<Terminal>("");
    seq.push_back(sym);
}

Cadeia::Cadeia(std::shared_ptr<Symbol>& s){
    seq.clear();
    seq.push_back(s);
}
Cadeia::Cadeia(std::vector<std::shared_ptr<Symbol>>& _seq){
    seq.clear();
    for (auto it = _seq.begin(); it != _seq.end(); it++){
        if ((*it)->isTerminal()){
            std::shared_ptr<Terminal> t = \
                        std::dynamic_pointer_cast<Terminal>(*it);
            std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(*t);
            seq.push_back(sym);
        }else{
            std::shared_ptr<NaoTerminal> t = \
                        std::dynamic_pointer_cast<NaoTerminal>(*it);
            std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>(*t);
            seq.push_back(sym);
        }
    }
}

Cadeia::Cadeia(Cadeia const& c){
    seq.clear();
    for (auto it = c.seq.begin(); it != c.seq.end(); it++){
        if ((*it)->isTerminal()){
            std::shared_ptr<Terminal> t = \
                        std::dynamic_pointer_cast<Terminal>(*it);
            std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(*t);
            seq.push_back(sym);
        }else{
            std::shared_ptr<NaoTerminal> t = \
                        std::dynamic_pointer_cast<NaoTerminal>(*it);
            std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>(*t);
            seq.push_back(sym);
        }
    }
}

Symbol& Cadeia::operator[](int idx){
    if (idx > (int) seq.size() - 1) throw "Índice fora do intervalo";
    return *seq[idx];
}

bool Cadeia::operator==(Cadeia const& rhs) const{
    if (seq.size() != rhs.seq.size()) return false;

    for (int i = 0; i < (int) seq.size(); i++){
        if ((*seq[i]).isTerminal() != (*rhs.seq[i]).isTerminal()){
            return false;

        }else if((*seq[i]).isTerminal()){
            std::shared_ptr<Terminal> t1 = \
                std::dynamic_pointer_cast<Terminal>(seq[i]);
            std::shared_ptr<Terminal> t2 = \
                std::dynamic_pointer_cast<Terminal>(rhs.seq[i]);
            if ( !(  (*t1) == (*t2)  )){
                return false;
            }
            
        }else{
            std::shared_ptr<NaoTerminal> t1 = \
                std::dynamic_pointer_cast<NaoTerminal>(seq[i]);
            std::shared_ptr<NaoTerminal> t2 = \
                std::dynamic_pointer_cast<NaoTerminal>(rhs.seq[i]);
            if ( !(  (*t1) == (*t2)  )){
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<< (std::ostream &out, const Cadeia &c){
    for (auto it = c.seq.begin(); it != c.seq.end(); it++){
        if ((**it).isTerminal()){
            std::shared_ptr<Terminal> t1 = \
                std::dynamic_pointer_cast<Terminal>((*it));
            out << *t1;
        }else{
            std::shared_ptr<NaoTerminal> t1 = \
                std::dynamic_pointer_cast<NaoTerminal>((*it));
            out << *t1;
        }
    }
    return out;
}

void Cadeia::conjuntoTerminais(std::set<Terminal>& out){
    out.clear();
    for (auto it = seq.begin(); it != seq.end(); it++){
        if ((**it).isTerminal()){
            std::shared_ptr<Terminal> t1 = \
                std::dynamic_pointer_cast<Terminal>((*it));
            if (!(*t1).vazio()){
                out.insert(*t1);
            } 
        }
    }
}
void Cadeia::conjuntoNaoTerminais(std::set<NaoTerminal>& out){
    out.clear();
    for (auto it = seq.begin(); it != seq.end(); it++){
        if ( !((**it).isTerminal()) ){
            std::shared_ptr<NaoTerminal> t1 = \
                std::dynamic_pointer_cast<NaoTerminal>((*it));
            out.insert(*t1);
        }
    }
}

int Cadeia::qtdSimbolos(){
    if (*seq[0] == Terminal("")){
        return 0;
    }else{
        return seq.size();
    }   
}

std::vector<std::shared_ptr<Symbol>>::iterator Cadeia::find(
    std::shared_ptr<Symbol>& nt
)
{
    auto it = seq.begin();
    for (; it != seq.end(); it++){
        if (**it == *nt){
            return it;
        }
    }
    return end();
}
std::vector<std::shared_ptr<Symbol>>::iterator Cadeia::find(
    std::shared_ptr<Symbol>& nt, 
    std::vector<std::shared_ptr<Symbol>>::iterator& pos
)
{
    auto it = pos+1;
    for (; it != seq.end(); it++){
        if (**it == *nt){
            return it;
        }
    }
    return end();
}

std::vector<std::shared_ptr<Symbol>>::iterator Cadeia::end(){
    return seq.end();
}

/*
Coloca um ponto na cadeia, na primeira posição. Se a cadeia já possui ponto, 
nada é feito.
*/
void Cadeia::itemLR0(){
    // Caso: cadeia vazia
    if (seq.size() == 1 && (*seq[0] == Terminal(""))){
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
        seq.clear();
        seq.push_back(sym);
    }

    // Verifica se já não possui ponto
    auto it = seq.begin();
    for (int i = 0; i < (int) seq.size(); i++){
        if (**it == Terminal(".")){
            return;
        }
        it++;
    }

    // Adiciona ponto na primeira posição
    std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
    seq.insert(seq.begin(),sym);
}

/*
Coloca um ponto na cadeia, na posição especificada empurrado para frente os 
símbolos após. Se a cadeia já possui ponto, nada é feito.
*/
void Cadeia::itemLR0(int pos){
    if(pos > ((int)seq.size())){
        throw "Índice inválido de posição";
    }else if((seq.size() == 1 && (*seq[0] == Terminal("")) && pos == 1)){
        throw "Índice inválido de posição";
    }else if (pos == 0){
        itemLR0();
    }

    // Verifica se já não possui ponto
    auto it = seq.begin();
    for (int i = 0; i < (int) seq.size(); i++){
        if (**it == Terminal(".")){
            return;
        }
        it++;
    }
    
    // Adiciona ponto na posição especificada
    it = seq.begin();
    for (int i = 0; i < (int) seq.size(); i++){
        if (i == pos) break;
        it++;
    }
    std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
    seq.insert(it,sym);
}

/*
Avança o ponto em uma posição. Se ele já estiver na última posição, nada é 
feito. A operação é in-place, ou seja, o objeto é alterado.
*/
void Cadeia::avanca(){
    // Procura o ponto
    auto it = seq.begin();
    for (; it != seq.end(); it++){
        if (**it == Terminal(".")) break;
    }

    // Cadeia não possui ponto
    if (it == seq.end()){ return;}
    // Ponto já na última posição
    if ( (it+1) == seq.end()){ return;}

    // Ponto será adicionado na última posição
    if ( (it+2) == seq.end()){
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
        seq.erase(it);
        seq.push_back(sym);
        return;
    }

    // Coloca o ponto após o símbolo seguinte
    std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(".");
    seq.insert(it+2, sym);
    // Deleta o ponto onde estava
    it = seq.begin();
    for (; it != seq.end(); it++){
        if (**it == Terminal(".")) break;
    }
    seq.erase(it);
}

/*
Verifica se dado o símbolo, o ponto da cadeia deve avançar. Em outras palavras
verifica se o símbolo fornecido é o seguinte ao ponto.
*/
bool Cadeia::deveAvancar(std::shared_ptr<Symbol>& sym){
    // Procura o ponto
    auto it = seq.begin();
    for (; it != seq.end(); it++){
        if (**it == Terminal(".")) break;
    }

    // Cadeia não possui ponto
    if (it == seq.end()){ return false;}
    // Ponto já na última posição
    if ( (it+1) == seq.end()){ return false;}

    // Colocaria o ponto após o símbolo seguinte: verifica o caractere seguinte
    if (**(it+1) == *sym){
        return true;
    }else{
        return false;
    }
}

/*
Verifica as duas cadeias são iguais ignorando o ponto. Também funciona com 
cadeias sem ponto.
*/
bool Cadeia::igualSemPonto(Cadeia const& rhs) const{
    if (abs(seq.size() - rhs.seq.size()) > 1) return false;

    if (*this == rhs){
        return true;
    }

    int j = 0;
    for (int i = 0; i < (int) seq.size(); i++){
        if((*seq[i]).isTerminal()){
            std::shared_ptr<Terminal> t1 = \
                        std::dynamic_pointer_cast<Terminal>(seq[i]);
            if ((*t1) == Terminal(".")){
                i++;
                t1 = std::dynamic_pointer_cast<Terminal>(seq[i]);
            }
        }
        if((*rhs.seq[j]).isTerminal()){
            std::shared_ptr<Terminal> t2 = \
                        std::dynamic_pointer_cast<Terminal>(rhs.seq[j]);
            if ((*t2) == Terminal(".")){
                j++;
                t2 = std::dynamic_pointer_cast<Terminal>(rhs.seq[j]);
            }
        }


        if ((*seq[i]).isTerminal() != (*rhs.seq[j]).isTerminal()){
            return false;

        }else if((*seq[i]).isTerminal()){
            std::shared_ptr<Terminal> t1 = \
                std::dynamic_pointer_cast<Terminal>(seq[i]);

            std::shared_ptr<Terminal> t2 = \
                std::dynamic_pointer_cast<Terminal>(rhs.seq[j]);

            if ( !(  (*t1) == (*t2)  )){
                return false;
            }
            
        }else{
            std::shared_ptr<NaoTerminal> t1 = \
                std::dynamic_pointer_cast<NaoTerminal>(seq[i]);
            std::shared_ptr<NaoTerminal> t2 = \
                std::dynamic_pointer_cast<NaoTerminal>(rhs.seq[j]);
            if ( !(  (*t1) == (*t2)  )){
                return false;
            }
        }
        j++;
    }
    return true;
}

