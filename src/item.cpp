#include "item.h"
#include "cadeia.h"

Item::Item()
:lhs("S")
{
    rhs = std::make_shared<Cadeia>();
}
Item::Item(Producao& p)
:lhs(p.label())
{
    Cadeia c = p[0];
    rhs = std::make_shared<Cadeia>(c);
}
Item::Item(Producao& p, int pos)
:lhs(p.label())
{
    if (pos >= p.qtdCadeias() || pos < 0){
        throw "Índice inválido para cadeias";
    }
    rhs = std::make_shared<Cadeia>(p[pos]);
}

Cadeia& Item::getCadeia(){
    return *rhs;
}

std::ostream& operator<< (std::ostream &out, const Item& it){
    out << it.lhs << " ===> ";
    out << *it.rhs;
    return out;
}