#include "symbol.h"

#include <ostream>
#include <iostream>
#include <ctype.h>

/* Métodos de Symbol */
bool Symbol::operator==(Symbol const& rhs) const{
    return this->symbol == rhs.symbol;
}

bool Symbol::operator<(Symbol const& d) const{
    return (this->symbol < d.symbol); 
}

/* Métodos de Terminal */
Terminal::Terminal(std::string _symbol){
    if (isspace(_symbol[0])) throw "Terminal espaço é inválido";
    
    symbol = _symbol;
    isVazio = false;
    isFim = false;

    if (_symbol == "") isVazio = true;
    if (_symbol == "$") isFim = true; 
}

bool Terminal::vazio(){
    return isVazio;
}
bool Terminal::fim(){
    return isFim;
}
bool Terminal::isTerminal(){
    return true;
}
std::ostream& operator<< (std::ostream &out, const Terminal &t){
    if (t.isVazio){
        out << "(vazio)";
    }else{
        out << t.symbol;
    }
    return out; 
} 



/* Métodos de Não-Terminal */
NaoTerminal::NaoTerminal(std::string _symbol){
    if (_symbol.size() < 1 || !isalpha(_symbol[0]) || isspace(_symbol[0])){
        throw "Nome invalido para nao-terminal";
    }
    symbol = _symbol;
}

bool NaoTerminal::isTerminal(){
    return false;
}
std::ostream& operator<< (std::ostream &out, const NaoTerminal &nt){
    out << "<" << nt.symbol << ">";
    return out; 
}
int NaoTerminal::labelSize(){
    return symbol.size();
}
