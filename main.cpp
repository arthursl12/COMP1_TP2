#include <iostream>
#include <string>

#include "lex.h"
#include "conj.h"
#include "gram.h"
#include "utils.h"
#include "tests/gram_exemplos.h"
#include "tests/closure_goto.h"
#include "tests/conj_itens.h"

int main(int argc, char* argv[]){
    std::set<std::set<std::shared_ptr<Item>>> out;
    out.clear();
    cria_sets_manual(out);

    Gramatica g;
    cria_gram_goto(g);
    gramaticaEstendida(g);

    ConjuntoItens c;
    conjuntosItens(c, g);

    (c.qtdConjuntos() == out.size());

    bool possuiConj = false;
    for (auto conj: out){
        auto it = c.find(conj);
        if (it != c.end()){
            possuiConj = true;
        }else{
            std::cout << "Conjunto Ausente:" << std::endl;
            for (auto elm0 : conj){
                std::cout << "\t" << *elm0 << std::endl;
            }
        }
        (possuiConj == true);
    }



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