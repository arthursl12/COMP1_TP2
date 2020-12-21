#include <iostream>
#include <string>

#include "lex.h"

int main(int argc, char* argv[]){
    std::string entrada = "12+12";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);

    std::cout << std::endl;
    entrada = "12+ +12";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);

    std::cout << std::endl;
    entrada = "12 <> (1.1 + -1.001E1)";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);
    return 0;
    
}