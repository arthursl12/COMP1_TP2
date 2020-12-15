#include <iostream>
#include <string>

#include "lex.h"

int main(int argc, char* argv[]){
    std::string entrada = "var1 <> (var2 + var3)";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);

    std::cout << std::endl;
    std::cout << "STOLL" << std::endl;
    std::cout << std::stoll("12") << std::endl;
    std::cout << std::stoll("-12") << std::endl;
    std::cout << std::stoll("+12") << std::endl;
    // STOLL (long long int) funciona com sinal na frente

    std::cout << "STOD" << std::endl;
    std::cout << std::stod("12.") << std::endl;
    std::cout << std::stod("-12.") << std::endl;
    std::cout << std::stod("+12.") << std::endl;

    std::cout << std::stod("-12.001E10") << std::endl;

    isUnsignedReal("12.001");



    return 0;
}