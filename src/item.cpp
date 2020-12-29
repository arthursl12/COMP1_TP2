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


NaoTerminal Item::label(){
    return lhs;
}

/*
Avança o ponto em uma posição. Se ele já estiver na última posição, nada é 
feito. A operação é in-place, ou seja, a cadeia do objeto é alterada.
*/
void Item::avanca(){
    rhs->avanca();
}

/*
Verifica se dado o símbolo, o ponto da cadeia deve avançar. Em outras palavras
verifica se o símbolo fornecido é o seguinte ao ponto.
*/
bool Item::deveAvancar(std::shared_ptr<Symbol>& sym){
    return (rhs->deveAvancar(sym));
}

/*
Verifica os dois itens são iguais ignorando o ponto das cadeias
*/
bool Item::igualSemPonto(Item const& oth) const{
    if (rhs->qtdSimbolos() != oth.rhs->qtdSimbolos()) return false;
    if (!(lhs == oth.lhs)){
        return false;
    }

    return rhs->igualSemPonto(*oth.rhs);
}
