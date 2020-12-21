#ifndef LEX_H
#define LEX_H

#include <string>

bool isAddOp(std::string op);
bool isMulOp(std::string op);
bool isSpecOp(std::string op);
bool isRelOp(std::string op);
bool isOperator(std::string op);
bool isDelimiter(std::string ch);
bool isIdentifier(std::string str);
bool isUnsignedInteger(std::string str);
bool isUnsignedReal(std::string str);
bool isConstant(std::string str);
std::string subString(std::string str, int left, int right);
void findTokens(std::string program);

#endif /* LEX_H */