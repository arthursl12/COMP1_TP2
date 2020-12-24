#include "cadeia.h"
#include "symbol.h"

#include <iostream>
#include <ostream>

Cadeia::Cadeia(){
    seq.clear();
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