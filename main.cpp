#include <iostream>
#include <string>

#include "lex.h"
#include "conj.h"
#include "gram.h"
#include "utils.h"
#include "tests/gram_exemplos.h"
#include "tests/closure_goto.h"
#include "tests/conj_itens.h"
#include "tests/action_goto.h"

int main(int argc, char* argv[]){
    // Gramatica g;
    // cria_gram_goto(g);
    // gramaticaEstendida(g);

    // std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>> tabAction;
    // std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>> tabGoto;

    // tabActionGoto(tabAction, tabGoto, g);
    // print_action_goto_manual(tabAction, tabGoto);


    Gramatica g;
    cria_gram_1(g);

    std::vector<std::shared_ptr<Symbol>> cad;
    std::shared_ptr<Symbol> sym;        
    Cadeia c;

    // E -> TE'
    cad.clear();
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<NaoTerminal>("E\'"));
    c = Cadeia(cad);
    g.getProdIndex(NaoTerminal("E"),c) == 0;

    // E' -> +TE' | (vazio)
    cad.clear();
    cad.push_back(std::make_shared<Terminal>("+"));
    cad.push_back(std::make_shared<NaoTerminal>("T"));
    cad.push_back(std::make_shared<NaoTerminal>("E\'"));
    c = Cadeia(cad);
    (g.getProdIndex(NaoTerminal("E\'"),c) == 1);


    // std::string entrada = "12+12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada);

    // std::cout << std::endl;
    // entrada = "12+ +12";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada);

    // std::cout << std::endl;
    // entrada = "12 <> (1.1 + -1.001E1)";
    // std::cout << "Programa: " << entrada << std::endl;
    // findTokens(entrada);
    return 0;
    
}