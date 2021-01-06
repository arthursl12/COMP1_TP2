#include "lex.h"
#include "symbol.h"

#include <iostream>
#include <memory>
#include <vector>

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

bool isNOT(std::string op){
    return op == "NOT";
}

bool isOperator(std::string op){
    if (isAddOp(op) || isMulOp(op) || isSpecOp(op) || isRelOp(op) || isNOT(op))
        return true;
    return false;
}

std::shared_ptr<Symbol> operatorToSymbol(std::string op){
    std::shared_ptr<Symbol> sym;
    if (isAddOp(op)){
        sym = std::make_shared<Terminal>("ADDOP");
    }else if (isMulOp(op)){
        sym = std::make_shared<Terminal>("MULOP");
    }else if (isSpecOp(op)){
        sym = std::make_shared<Terminal>("SPECOP");
    }else if (isRelOp(op)){
        sym = std::make_shared<Terminal>("RELOP");
    }else if (isNOT(op)){
        sym = std::make_shared<Terminal>("NOT");
    }else{
        throw "Operador Inválido";
    }
    return sym;
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
    if ((str[i] != '.' && (str[i] != 'E' && str[i] != 'e')) || i < 1){
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
    if (str[j] != 'E' && str[j] != 'e'){
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

bool isValidConstantSign(std::string const& program, 
                         int const left, int const right)
{
    std::string oper = program.substr(right,1);
    if (oper != "+" && oper != "-"){
        return false;
    }else if (left != right){
        return false;
    }else if (isDelimiter(program.substr(right+1,1))){
        return false;
    }else if (program[left-1] == 'E' || program[left-1] == 'e'){
        return false;
    }else if (isdigit(program[left-1])){
        return false;
    }else if (program.substr(right+1,3) == "NOT"){
        return false;
    }else if (isIdentifier(program.substr(right+1,1))){
        return false;
    }else {
        return true;
    }
}

bool isValidTermSign(std::string const& program, 
                     int const left, int const right)
{
    std::string oper = program.substr(right,1);
    if (oper != "+" && oper != "-"){
        return false;
    }else if (left != right){
        return false;
    }else if (isspace(program[right]) != 0){
        return false;
    }else if (isValidConstantSign(program,left, right)){
        return false;
    }else if (isdigit(program[left-1]) && program[right+1] == '('){
        return false;
    }else if (isdigit(program[left-1]) && isdigit(program[right+1])){
        return false;
    }else if (program[left-1] == 'E' || program[left-1] == 'e'){
        return false;
    }


    if (program[right+1] == '('){
        return true;
    }else if(isIdentifier(std::string(1,program[right+1])) && !isdigit(program[left-1])){
        return true;
    }else if(program.substr(right+1,3) == "NOT"){
        return true;
    }else if(isdigit(program[right+1]) && !isValidConstantSign(program,left,right)){
        return true;
    }

    return false;
}

/*
TOKENS:
RELOP, ADDOP, MULOP, SPECOP, identifier, constant, NOT

N-Ts: 
EXPR_LS, EXPR, S_EXPR, T, FA, FR, SIGN

T-s:
(, ), ,, +, - 
*/
/*
Retorna 'true' se há expressões à frente. 'false' do contrário.
*/
bool findTokens(
    std::string program, 
    std::vector<std::shared_ptr<Symbol>>& entrada,
    int& left, int& right)
{   
    entrada.clear();
    
    // int left = 0, right = 0;
    int length = program.length();
    std::cout.setf(std::ios::boolalpha);

    // std::cout << "LEN: " << length << std::endl;
    while (right <= length && left <= right) {
        // std::cout << "isDelim?: " << program[right] << " -> " << isDelimiter(std::to_string(program[right])) << std::endl;
        if (!isDelimiter(std::string(1,program[right]))){
            right++;
            // std::cout << "isDelim?: " << program[right] << " -> " << isDelimiter(std::to_string(program[right])) << std::endl;
        }
        if (right > length){
            break;
        }
        // std::cout << "isDelim?: " << program[right] << " -> " << isDelimiter(std::string(1,program[right])) << std::endl;
        if (isValidConstantSign(program, left, right)){
            right++;
            while (right < length && !isDelimiter(std::string(1,program[right])))
                right++;
            if (program[right-1] == 'E' || program[right-1] == 'e'){
                right++;
                while (right < length && !isDelimiter(std::string(1,program[right])))
                    right++;
            }
            std::string subStr = subString(program, left, right - 1);
            // std::cout << "\tsubstr1: " << subStr << std::endl;
            if (isConstant(subStr) == true){
                std::cout << "Valid Signed Constant : " << subStr << std::endl;
                std::shared_ptr<Symbol> cst = \
                                        std::make_shared<Terminal>("constant");
                entrada.push_back(cst);
            }
            left = right;
        }else if (isDelimiter(std::string(1,program[right])) && left == right) {
            // std::cout << "PR1:" << program[right] << std::endl;
            if (isOperator(program.substr(right,2))){
                std::cout << "Valid operator (2-char): " << \
                    program.substr(right,2) << std::endl;
                std::string subStr = program.substr(right,2);
                entrada.push_back(operatorToSymbol(subStr));
                right += 2;
                left = right; 
            }else if (isOperator(program.substr(right,1)) 
                      && !isValidConstantSign(program, left, right) 
                      && !isValidTermSign(program,left,right)){
                std::cout << "Valid operator (1-char): " << 
                    program[right] << std::endl;
                std::string subStr = program.substr(right,1);
                entrada.push_back(operatorToSymbol(subStr));
                right++;
                left = right;
            }else{
                // std::cout << "Delimitador: " << program[right] << std::endl;
                if (program[right] == ','){
                    // Fim da expressão
                    right++;
                    left = right;
                    
                    if (right >= length){
                        throw "Vírgula inapropriada no fim";
                    }else{
                        return true;
                    }
                }else if (isspace(program[right]) == 0){
                    std::string str = std::string(1,program[right]);
                    std::shared_ptr<Symbol> sym = \
                                        std::make_shared<Terminal>(str);
                    entrada.push_back(sym);
                }
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
            if (isOperator(subStr)){
                std::cout << "Valid operator (keyword) : " << subStr << std::endl;
                entrada.push_back(operatorToSymbol(subStr));
            }else if (isIdentifier(subStr) &&
                !isDelimiter(std::to_string(program[right - 1]))){
                std::cout << "Valid Identifier : " << subStr << std::endl;
                std::shared_ptr<Symbol> id = std::make_shared<Terminal>("id");
                entrada.push_back(id);
            }else if (isConstant(subStr) == true){
                std::cout << "Valid Unsigned Constant : " << subStr << std::endl;
                if (program[right-1] == 'E' || program[right-1] == 'e'){
                    right++;
                    while (right < length && !isDelimiter(std::string(1,program[right])))
                        right++;
                }
                std::shared_ptr<Symbol> cst = \
                                        std::make_shared<Terminal>("constant");
                entrada.push_back(cst);
            }else if (!isIdentifier(subStr) && 
                     !isDelimiter(std::to_string(program[right - 1]))){
                std::cout << "Invalid Identifier : " << subStr << std::endl;
            }
            left = right;
            // std::cout << std::endl;
        }
        // std::cout << "right = " << right << " left = " << left << std::endl;
        
    }
    return false;
}