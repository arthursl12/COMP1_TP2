#include <iostream>
#include <string>

#include "lex.h"

int main(int argc, char* argv[]){
    std::string prog = "12+12";
    isValidSign(prog,2,2);


    std::string entrada = "12++12";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);

    std::cout << std::endl;
    std::cout << 12+ +12 << std::endl;
    entrada = "12 <> (1.1 + -1.001E1)";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);
    return 0;
    
}