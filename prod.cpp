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


std::ostream& operator<< (std::ostream &out, const Producao& p){
    out << p.lhs << " ===> ";
    out << *p.rhs[0];

    for (auto it = (p.rhs.begin() + 1); it != p.rhs.end(); it++){
        out << std::endl;
        out << "\t | " << **it;
    }
    return out;
}
