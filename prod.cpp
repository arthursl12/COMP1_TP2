#include "prod.h"

Producao::Producao()
:lhs("ZZZ")
{
}

Producao::Producao(
    NaoTerminal _lhs, std::vector<std::shared_ptr<Cadeia>> _rhs)
    : lhs(_lhs)
{
    rhs.clear();
    for (auto it = _rhs.begin(); it != _rhs.end(); it++){
        rhs.push_back(*it);
    }
}

Cadeia& Producao::operator[](int idx){
    if (idx > (int) rhs.size() - 1) throw "Índice fora do intervalo";
    return *rhs[idx];
}

NaoTerminal Producao::label(){
    return lhs;
}

