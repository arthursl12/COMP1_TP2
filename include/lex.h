#ifndef LEX_H
#define LEX_H

#include "symbol.h"

#include <string>
#include <memory>
#include <vector>

bool isAddOp(std::string op);
bool isMulOp(std::string op);
bool isSpecOp(std::string op);
bool isRelOp(std::string op);
bool isNOT(std::string op);
bool isOperator(std::string op);
bool isDelimiter(std::string ch);
bool isIdentifier(std::string str);
bool isUnsignedInteger(std::string str);
bool isUnsignedReal(std::string str);
bool isConstant(std::string str);
bool isValidConstantSign(std::string const& program, 
                         int const left, int const right);
bool isValidTermSign(std::string const& program, 
                         int const left, int const right);
std::string subString(std::string str, int left, int right);
std::shared_ptr<Symbol> operatorToSymbol(std::string op);
void findTokens(std::string program, 
                std::vector<std::shared_ptr<Symbol>>& entrada);

#endif /* LEX_H */