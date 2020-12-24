#include "cadeia.h"
#include "symbol.h"

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