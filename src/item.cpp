#include "item.h"
#include "cadeia.h"

Item::Item()
:lhs("S")
{
    rhs = std::make_shared<Cadeia>();
    rhs->itemLR0();
}
Item::Item(Producao& p)
:lhs(p.label())
{
    Cadeia c = p[0];
    rhs = std::make_shared<Cadeia>(c);
    rhs->itemLR0();
}
Item::Item(Producao& p, int pos)
:lhs(p.label())
{
    if (pos >= p.qtdCadeias() || pos < 0){
        throw "Índice inválido para cadeias";
    }
    rhs = std::make_shared<Cadeia>(p[pos]);
    rhs->itemLR0();
}

Item::Item(Item const& oth)
:lhs(oth.lhs)
{
    rhs = std::make_shared<Cadeia>(*oth.rhs);
}

Cadeia& Item::getCadeia(){
    return *rhs;
}

std::ostream& operator<< (std::ostream &out, const Item& it){
    out << it.lhs << " ===> ";
    out << *it.rhs;
    return out;
}

bool Item::operator==(Item const& oth) const{
    if (rhs->qtdSimbolos() != oth.rhs->qtdSimbolos()) return false;

    if (!(lhs == oth.lhs)){
        return false;
    }

    if (*rhs == (*oth.rhs)){
        return true;
    }else{
        return false;
    }
}

void Item::avanca(){
    rhs->avanca();
}

NaoTerminal Item::label(){
    return lhs;
}