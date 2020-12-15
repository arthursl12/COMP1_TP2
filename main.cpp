#include <iostream>
#include <string>

#include "lex.h"

int main(int argc, char* argv[]){
    std::string entrada = "var1 <> var2";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);
    return 0;
}