#include "lex.h"

#include <iostream>

/* Funções inspiradas em:
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
        return true;
    return false;
}

bool isDelimiter(std::string ch) {
    if (
        isspace(ch[0]) != 0 || isOperator(ch) ||
        ch == "," || ch == "(" || ch == ")"
    ){
        return (true);
    }else{
        return (false);
    }
}

bool isIdentifier(std::string str){
    // Não pode começar com número
    if (!isalpha(str[0])){
        return false;
    }
    return true;
}

std::string subString(std::string str, int left, int right) {
   std::string subStr = str.substr(left, right - left + 1);
   return subStr;
}

bool isUnsignedInteger(std::string str){
    if (str.length() < 1) return false;
    for (unsigned int i = 0; i < str.length(); i++){
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' &&
            str[i] != '3' && str[i] != '4' && str[i] != '5' &&
            str[i] != '6' && str[i] != '7' && str[i] != '8' &&
            str[i] != '9'){
                return false;
        }
    }
    return true;
}

bool isUnsignedReal(std::string str){
    // Verifica a parte inteira
    if (str.length() < 1) return false;
    unsigned int i = 0;
    for (i = 0; i < str.length(); i++){
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' &&
            str[i] != '3' && str[i] != '4' && str[i] != '5' &&
            str[i] != '6' && str[i] != '7' && str[i] != '8' &&
            str[i] != '9'){
                break;
        }
    }
    // String acabou: número inteiro puro (ainda conta como real)
    if (i == str.length()){
        return true;
    }
    // Caractere que não ponto ou E (da potência); parte inteira vazia
    if ((str[i] != '.' && str[i] != 'E') || i < 1){
        return false;
    }

    // Verifica a parte decimal
    bool decimal = false;
    if (str[i] == '.') decimal = true;
    unsigned int j = i;
    if (decimal){
        j = j+1;
        for (; j < str.length(); j++){
            if (str[j] != '0' && str[j] != '1' && str[j] != '2' &&
                str[j] != '3' && str[j] != '4' && str[j] != '5' &&
                str[j] != '6' && str[j] != '7' && str[j] != '8' &&
                str[j] != '9'){
                    break;
            }
        }
    }

    // String acabou: número decimal (sem potência)
    if (j == str.length()){
        return true;
    }
    // Caractere seguinte não é o E da potência
    if (str[j] != 'E'){
        return false;
    }

    // Verifica potência
    unsigned int k = j+1;
    if (str[k] == '+' || str[k] == '-') k++;
    for (; k < str.length(); k++){
        if (str[k] != '0' && str[k] != '1' && str[k] != '2' &&
            str[k] != '3' && str[k] != '4' && str[k] != '5' &&
            str[k] != '6' && str[k] != '7' && str[k] != '8' &&
            str[k] != '9'){
                break;
        }
    }
    // String acabou: número real válido
    if (k == str.length()){
        return true;
    }else{
        return false;
    }
}

bool isConstant(std::string str){
    if ((str[0] == '+' || str[0] == '-') && 
        (!isDelimiter(std::string(1,str[1])))){
        std::string num = str.substr(1);
        return (isUnsignedInteger(num) || isUnsignedReal(num));
    }else if (str[0] != '+' && str[0] != '-'){
        return (isUnsignedInteger(str) || isUnsignedReal(str));
    }else{
        return false;
    }
}

bool isValidSign(std::string const& program, int const left, int const right){
    std::string oper = program.substr(right,1);
    if (oper != "+" && oper != "-"){
        return false;
    }else if (left != right){
        return false;
    }else if (isDelimiter(program.substr(right+1,1))){
        return false;
    }else if (program[left-1] == 'E'){
        return false;
    }else if (isdigit(program[left-1])){
        return false;
    }else {
        return true;
    }
}

void findTokens(std::string program){
    int left = 0, right = 0;
    int length = program.length();
    // std::cout << "LEN: " << length << std::endl;
    while (right <= length && left <= right) {
        if (!isDelimiter(std::string(1,program[right]))){
            right++;
        }
        if (right > length){
            break;
        }
        // std::cout << "isDelim?: " << program[right] << " -> " << isDelimiter(std::to_string(program[right])) << std::endl;
        if (isValidSign(program, left, right)){
            right++;
            while (right < length && !isDelimiter(std::string(1,program[right])))
                right++;
            std::string subStr = subString(program, left, right - 1);
            // std::cout << "\tsubstr1: " << subStr << std::endl;
            if (isConstant(subStr) == true){
                 std::cout << "Valid Signed Constant : " << subStr << std::endl;
            }
            left = right;
        }else if (isDelimiter(std::string(1,program[right])) && left == right) {
            // std::cout << "PR1:" << program[right] << std::endl;
            if (isOperator(program.substr(right,2))){
                std::cout << "Valid operator (2-char): " << \
                    program.substr(right,2) << std::endl;
                right += 2;
                left = right; 
            }else if (isOperator(program.substr(right,1)) && !isValidSign(program, left, right)){
                std::cout << "Valid operator (1-char): " << 
                    program[right] << std::endl;
                right++;
                left = right;
            }else{
                right++;
                left = right;
            }
        }else if((isDelimiter(std::string(1,program[right])) && 
                 left != right) || (right == length && left != right)){
            // std::cout << "PR2:" << program[right] << std::endl;
            std::string subStr = subString(program, left, right - 1);
            // std::cout << "\tsubstr: " << subStr << std::endl;
            // if (isValidKeyword(subStr) == true)
            //     printf("Valid keyword : '%s'\n", subStr);

            // else if (isRealNumber(subStr) == true)
            //     printf("Real Number : '%s'\n", subStr);
            if (isIdentifier(subStr) &&
                !isDelimiter(std::to_string(program[right - 1]))){
                std::cout << "Valid Identifier : " << subStr << std::endl;
            }else if (isConstant(subStr) == true){
                 std::cout << "Valid Unsigned Constant : " << subStr << std::endl;
            }else if (!isIdentifier(subStr) && 
                     !isDelimiter(std::to_string(program[right - 1]))){
                std::cout << "Invalid Identifier : " << subStr << std::endl;
            }
            left = right;
            // std::cout << std::endl;
        }
        // std::cout << "right = " << right << " left = " << left << std::endl;
        
    }
}