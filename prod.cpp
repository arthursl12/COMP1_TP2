#include "prod.h"

Producao::Producao()
:lhs("S")
{

    rhs.push_back(std::make_shared<Cadeia>());
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

/* Retorna a união dos conjuntos passados */
template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b){
  std::set<T> result = a;
  result.insert(b.begin(), b.end());
  return result;
}

void Producao::conjuntoTerminais(std::set<Terminal>& out){
    out.clear();
    for (auto it = rhs.begin(); it != rhs.end(); it++){
        std::set<Terminal> temp1;
        (**it).conjuntoTerminais(temp1);
        out = getUnion(out, temp1);
    }
}
void Producao::conjuntoNaoTerminais(std::set<NaoTerminal>& out){
    out.clear();
    for (auto it = rhs.begin(); it != rhs.end(); it++){
        std::set<NaoTerminal> temp1;
        (**it).conjuntoNaoTerminais(temp1);
        out = getUnion(out, temp1);
    }
}

int Producao::qtdCadeias(){
    return rhs.size();
}
