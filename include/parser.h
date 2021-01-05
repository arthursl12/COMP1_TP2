#ifndef PARSER_H
#define PARSER_H

#include "gram.h"

bool parser(std::vector<std::shared_ptr<Symbol>>& entrada, Gramatica& g);

#endif /* PARSER_H */