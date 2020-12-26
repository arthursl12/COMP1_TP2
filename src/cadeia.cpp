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
        seq.push_back(*it);
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
    std::shared_ptr<NaoTerminal>& nt
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
    std::shared_ptr<NaoTerminal>& nt, 
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