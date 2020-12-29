#include "action.h"

#include <iostream>

/* ACAO */
Acao::Acao(){
    tipo = "Acao (abstrato)";
}


/* ACCEPT */
Accept::Accept(){
    tipo = "Accept";
}
std::string Accept::getTipo(){
    return tipo;
}
std::ostream& operator<< (std::ostream &out, const Accept& ac){
    out << ac.tipo;
    return out;
}


/* ERROR */
Error::Error(){
    tipo = "Error";
}
std::string Error::getTipo(){
    return tipo;
}
std::ostream& operator<< (std::ostream &out, const Error& er){
    out << er.tipo;
    return out;
}


/* SHIFT */
/* Shift e Estado j (começa de 0) será empilhado */
Shift::Shift(int _estado_j){
    tipo = "Shift";
    estado_j = _estado_j;
}
std::string Shift::getTipo(){
    return tipo;
}
std::ostream& operator<< (std::ostream &out, const Shift& sh){
    out << sh.tipo << ": " << sh.estado_j;
    return out;
}


/* REDUCE */
/* Redução segundo a produção i (começa de 1) */
Reduce::Reduce(int _prod_i)
{
    prod_i = _prod_i;
    tipo = "Reduce";
    if (prod_i == 0)
        throw "Não-terminal inválido para redução: inicial da gramática aumentada";
}
std::string Reduce::getTipo(){
    return tipo;
}
std::ostream& operator<< (std::ostream &out, const Reduce& re){
    out << re.tipo << ": " << re.prod_i;
    return out;
} 
