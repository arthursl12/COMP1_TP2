#include <iostream>
#include <string>
#include <ctype.h> 


/* Inspirado em:
https://www.tutorialspoint.com/c-program-to-detect-tokens-in-a-c-program
*/

bool isAddOp(std::string op){
    if (op == "+" || op == "-" || op == "or")
        return true;
    else
        return false;
}

bool isMulOp(std::string op){
    if (op == "*" || op == "/" || op == "div" || op == "mod" || op == "and")
        return true;
    else
        return false;
}

/* SPECOP: sin, cos, log */
bool isSpecOp(std::string op){
    if (op == "sin" || op == "cos" || op == "log")
        return true;
    else
        return false;
}

bool isRelOp(std::string op){
    if (
        op == "="  || op == "<"  || op == ">" ||
        op == "<>" || op == "<=" || op == ">="
    ){
        return true;
    }else{
        return false;
    }
}

bool isOperator(std::string op){
    if (isAddOp(op) || isMulOp(op) || isSpecOp(op) || isRelOp(op))
        return (true);
    return (false);
}

bool isDelimiter(std::string ch) {
    // std::cout << isspace(ch[0]) << std::endl;
    if (
        isspace(ch[0]) != 0 || isOperator(ch) ||
        ch == "," || ch == ";" || ch == "(" || ch == ")" 
        || ch == "\n" || ch == " "
    ){
        return (true);
    }else{
        return (false);
    }
}

bool isIdentifier(std::string str){
    // Não pode começar com número
    if (!isalpha(str[0])){
        return (false);
    }

    return (true);
}

std::string subString(std::string str, int left, int right) {
   int i;
   std::string subStr = str.substr(left, right - left + 1);
   return subStr;
}

void findTokens(std::string program){
    int left = 0, right = 0;
    int length = program.length();
    while (right <= length && left <= right) {
        if (!isDelimiter(std::string(1,program[right]))){
            right++;
        }
        // std::cout << "isDelim?: " << program[right] << " -> " << isDelimiter(std::to_string(program[right])) << std::endl;
        if (isDelimiter(std::string(1,program[right])) && left == right){
            std::cout << "PR1:" << program[right] << std::endl;
            if (isOperator(program.substr(right,2))){
                std::cout << "Valid operator (2-char): " << \
                    program.substr(right,2) << std::endl;
                right += 2;
                left = right; 
            }else if (isOperator(program.substr(right,1))){
                std::cout << "Valid operator (1-char): " << 
                    program[right] << std::endl;
                right++;
                left = right;
            }else{
                right++;
                left = right;
            }
        }else if(isDelimiter(std::string(1,program[right])) && 
                 left != right || (right == length && left != right)){
            std::cout << "PR2:" << program[right] << std::endl;
            std::string subStr = subString(program, left, right - 1);
            std::cout << "Substr: " << subStr << std::endl;
            // if (isValidKeyword(subStr) == true)
            //     printf("Valid keyword : '%s'\n", subStr);
            // else if (isValidInteger(subStr) == true)
            //     printf("Valid Integer : '%s'\n", subStr);
            // else if (isRealNumber(subStr) == true)
            //     printf("Real Number : '%s'\n", subStr);
            if (isIdentifier(subStr) &&
                !isDelimiter(std::to_string(program[right - 1])))
                std::cout << "Valid Identifier : " << subStr << std::endl;
            else if (!isIdentifier(subStr) && 
                     !isDelimiter(std::to_string(program[right - 1])))
                std::cout << "Invalid Identifier : " << subStr << std::endl;
            left = right;
            std::cout << std::endl;
        }
        std::cout << "right = " << right << " left = " << left << std::endl;
        
    }
}

int main(int argc, char* argv[]){
    std::string entrada = "var1 <> var2";
    std::cout << "Programa: " << entrada << std::endl;
    findTokens(entrada);
    return 0;
}