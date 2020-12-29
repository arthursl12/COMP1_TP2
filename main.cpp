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
    Gramatica g;
    cria_gram_goto(g);
    gramaticaEstendida(g);

    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>> tabAction;
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>> tabGoto;

    tabActionGoto(tabAction, tabGoto, g);
    // print_action_goto_manual(tabAction, tabGoto);


    // Gramatica g;
    // cria_gram_4(g);

    // // FOLLOW(B) = FIRST(D) U {h} = {g,f,h}
    // std::set<Terminal> conj_follow;
    // conj_follow.insert(Terminal("g"));
    // conj_follow.insert(Terminal("f"));
    // conj_follow.insert(Terminal("h"));

    // std::set<Terminal> out;
    // std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("B");
    // g.follow(nt, out);


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