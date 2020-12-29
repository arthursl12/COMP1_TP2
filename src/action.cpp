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
Shift::Shift(int _j){
    tipo = "Shift";
    j = _j;
}
std::string Shift::getTipo(){
    return tipo;
}
std::ostream& operator<< (std::ostream &out, const Shift& sh){
    out << sh.tipo << ": " << sh.j;
    return out;
}


/* REDUCE */
Reduce::Reduce(NaoTerminal _A, Terminal _alpha)
: A(_A), alpha(_alpha)
{
    tipo = "Reduce";
    if (A == NaoTerminal("S\'"))
        throw "Não-terminal inválido para redução: inicial da gramática aumentada";
}
std::string Reduce::getTipo(){
    return tipo;
}
std::ostream& operator<< (std::ostream &out, const Reduce& re){
    out << re.tipo << ": " << re.A << " -> " << re.alpha;
    return out;
} 
