#ifndef ACTION_GOTO_H
#define ACTION_GOTO_H

#include "action.h"
#include "symbol.h"
#include "gram.h"
#include "conj.h"
#include "item.h"
#include "conj_itens.h"
#include "closure_goto.h"
#include "action_goto.h"

#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <utility>
#include <iomanip>

void ConjItensToVector(std::vector<std::set<std::shared_ptr<Item>>>& out_vect,
                       std::vector<std::set<std::shared_ptr<Item>>>& c_vect)
{
    std::set< std::set< std::shared_ptr<Item> >>  out;
    cria_sets_manual(out);
    for (auto conj: out){
        out_vect.push_back(conj);
    }

    Gramatica g;
    cria_gram_goto(g);
    gramaticaEstendida(g);

    ConjuntoItens c;
    conjuntosItens(c, g);

    for(auto it_estado = c.begin(); it_estado != c.end(); it_estado++){
        Elemento elm = **it_estado;
        std::set<std::shared_ptr<Item>> conj = elm.conj_item;
        std::cout << "Estado: " << elm.label << std::endl;
        
        for (std::shared_ptr<Item> ptr_item: conj){
            std::cout << "\t" << *ptr_item << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (auto it_conj = c.begin(); it_conj != c.end(); it_conj++){
        c_vect.push_back((**it_conj).conj_item);
    }
}


void print_action_goto_manual(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>>& tabGoto)
{   
    int SPC = 7;
    std::cout << "======ACTION======" << std::endl;
    auto linha0 = tabAction.begin();
    std::cout << "|" << std::setw(SPC) << "I" << std::setw(SPC);
    for (auto pares0: **linha0){
        std::cout << "|" << std::setw(SPC) << pares0.first << std::setw(SPC);
    }
    std::cout << "|" << std::endl;

    int i = 0;
    for(auto linha: tabAction){
        std::cout << "|" << std::setw(SPC) << "I" + std::to_string(i) << std::setw(SPC);
        for(auto par: *linha){
            if (par.second->getTipo() == "Error"){
                std::cout << "|" << std::setw(SPC) << "" << std::setw(SPC);
            }else if (par.second->getTipo() == "Shift"){
                std::shared_ptr<Shift> sft = \
                            std::dynamic_pointer_cast<Shift>(par.second);
                std::cout << "|" << std::setw(SPC) << *sft << std::setw(SPC-3);
            }else if (par.second->getTipo() == "Reduce"){
                std::shared_ptr<Reduce> red = \
                            std::dynamic_pointer_cast<Reduce>(par.second);
                std::cout << "|" << std::setw(SPC) << *red << std::setw(SPC-3);
            }else{
                std::cout << "|" << std::setw(SPC) << par.second->getTipo() << std::setw(SPC);
            }
        }
        i++;
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "======GOTO======" << std::endl;
    auto linha1 = tabGoto.begin();
    std::cout << "|" << std::setw(SPC) << "I" << std::setw(SPC);
    for (auto pares0: **linha1){
        std::cout << "|" << std::setw(SPC-1) << pares0.first << std::setw(SPC-1);
    }
    std::cout << "|" << std::endl;

    i = 0;
    for(auto linha: tabGoto){
        std::cout << "|" << std::setw(SPC) << "I" + std::to_string(i) << std::setw(SPC);
        for(auto par: *linha){
            if (par.second == -1){
                std::cout << "|" << std::setw(SPC) << "" << std::setw(SPC);
            }else{
                std::cout << "|" << std::setw(SPC) << par.second << std::setw(SPC);
            }
            
        }
        i++;
        std::cout << "|" << std::endl;
    }
}

void cria_action_goto_manual(
    std::vector<std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>>& tabAction,
    std::vector<std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>>>& tabGoto)
{
    //Produções
    // S' -> E  (1)
    // E -> E+T (2)
    // E -> T   (3)
    // T -> T*F (4)
    // T -> F   (5)
    // F -> (E) (6)
    // F -> id  (7)

    std::vector<std::set<std::shared_ptr<Item>>> out_vect;
    std::vector<std::set<std::shared_ptr<Item>>> c_vect;
    ConjItensToVector(out_vect, c_vect);

    std::vector<int> it;
    for(int i = 0; i < (int)out_vect.size(); i++){   it.push_back(i);}

    // for(int i = 0; i < (int)out_vect.size(); i++){
    //     for(int j = 0; j < (int)c_vect.size(); j++){
    //         if(conjuntosIguais(c_vect[j],out_vect[i],false)){
    //             it[i] = i;
    //         }
    //     }
    // }

    // for (auto el: it){
    //     std::cout << "\t" << el << std::endl;
    // }

    // bool possuiConj = false;
    // for (auto conj: out){
    //     possuiConj = false;
    //     auto it = c.find(conj);
    //     if (it != c.end()){
    //         possuiConj = true;
    //     }else{
    //         std::cout << "Conjunto Ausente:" << std::endl;
    //         for (auto elm0 : conj){
    //             std::cout << "\t" << *elm0 << std::endl;
    //         }
    //     }
    //     CHECK(possuiConj == true);
    // }

    // std::pair<Terminal,std::shared_ptr<Acao>> p_id;
    // std::pair<Terminal,std::shared_ptr<Acao>> p_mais;
    // std::pair<Terminal,std::shared_ptr<Acao>> p_estrela;
    // std::pair<Terminal,std::shared_ptr<Acao>> p_abre;
    // std::pair<Terminal,std::shared_ptr<Acao>> p_fecha;
    // std::pair<Terminal,std::shared_ptr<Acao>> p_fim;

    std::pair<Terminal,std::shared_ptr<Acao>> p_id = 
        std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Shift>(it[5]));
    std::pair<Terminal,std::shared_ptr<Acao>> p_mais = 
        std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Error>());
    std::pair<Terminal,std::shared_ptr<Acao>> p_estrela = 
        std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    std::pair<Terminal,std::shared_ptr<Acao>> p_abre = 
        std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Shift>(it[4]));
    std::pair<Terminal,std::shared_ptr<Acao>> p_fecha = 
        std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Error>());
    std::pair<Terminal,std::shared_ptr<Acao>> p_fim = 
        std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Error>());

    // std::pair<NaoTerminal,int> g_E;
    // std::pair<NaoTerminal,int> g_T;
    // std::pair<NaoTerminal,int> g_F;

    std::pair<NaoTerminal,int> g_E = \
        std::make_pair<NaoTerminal,int&>(NaoTerminal("E"),it[1]);
    std::pair<NaoTerminal,int> g_T = 
        std::make_pair<NaoTerminal,int&>(NaoTerminal("T"),it[2]);
    std::pair<NaoTerminal,int> g_F = 
        std::make_pair<NaoTerminal,int&>(NaoTerminal("F"),it[3]);

    
    //Estados: I0 -> I11
    // I0
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Shift>(it[5]));
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Error>());
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Shift>(it[4]));
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Error>());
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Error>());
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I0a;
    I0a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I0a->push_back(p_id);
    I0a->push_back(p_mais);
    I0a->push_back(p_estrela);
    I0a->push_back(p_abre);
    I0a->push_back(p_fecha);
    I0a->push_back(p_fim);
    tabAction.push_back(I0a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I0g;
    I0g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int&>(NaoTerminal("E"),it[1]);
    g_T = std::make_pair<NaoTerminal,int&>(NaoTerminal("T"),it[2]);
    g_F = std::make_pair<NaoTerminal,int&>(NaoTerminal("F"),it[3]);
    I0g->push_back(g_E);
    I0g->push_back(g_F);
    I0g->push_back(g_T);
    tabGoto.push_back(I0g);
    
    
    // I1
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Shift>(it[6]));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Error>());
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Accept>());
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I1a;
    I1a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I1a->push_back(p_id);
    I1a->push_back(p_mais);
    I1a->push_back(p_estrela);
    I1a->push_back(p_abre);
    I1a->push_back(p_fecha);
    I1a->push_back(p_fim);
    tabAction.push_back(I1a);
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I1g;
    I1g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    I1g->push_back(g_E);
    I1g->push_back(g_F);
    I1g->push_back(g_T);
    tabGoto.push_back(I1g);
    
    // I2
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Reduce>(3));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Shift>(it[7]));
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Reduce>(3));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Reduce>(3));
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I2a;
    I2a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I2a->push_back(p_id);
    I2a->push_back(p_mais);
    I2a->push_back(p_estrela);
    I2a->push_back(p_abre);
    I2a->push_back(p_fecha);
    I2a->push_back(p_fim);
    tabAction.push_back(I2a);
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I2g;
    I2g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    I2g->push_back(g_E);
    I2g->push_back(g_F);
    I2g->push_back(g_T);
    tabGoto.push_back(I2g);

    // I3
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Reduce>(5));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Reduce>(5));
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Reduce>(5));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Reduce>(5));
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I3a;
    I3a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I3a->push_back(p_id);
    I3a->push_back(p_mais);
    I3a->push_back(p_estrela);
    I3a->push_back(p_abre);
    I3a->push_back(p_fecha);
    I3a->push_back(p_fim);
    tabAction.push_back(I3a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I3g;
    I3g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    I3g->push_back(g_E);
    I3g->push_back(g_F);
    I3g->push_back(g_T);
    tabGoto.push_back(I3g);

    // I4
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Shift>(it[5]));
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Error>());
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Shift>(it[4]));
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Error>());
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Error>());
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I4a;
    I4a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I4a->push_back(p_id);
    I4a->push_back(p_mais);
    I4a->push_back(p_estrela);
    I4a->push_back(p_abre);
    I4a->push_back(p_fecha);
    I4a->push_back(p_fim);
    tabAction.push_back(I4a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I4g;
    I4g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int&>(NaoTerminal("E"),it[8]);
    g_T = std::make_pair<NaoTerminal,int&>(NaoTerminal("T"),it[2]);
    g_F = std::make_pair<NaoTerminal,int&>(NaoTerminal("F"),it[3]);
    I4g->push_back(g_E);
    I4g->push_back(g_F);
    I4g->push_back(g_T);
    tabGoto.push_back(I4g);

    // I5
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Reduce>(7));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Reduce>(7));
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Reduce>(7));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Reduce>(7));
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I5a;
    I5a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I5a->push_back(p_id);
    I5a->push_back(p_mais);
    I5a->push_back(p_estrela);
    I5a->push_back(p_abre);
    I5a->push_back(p_fecha);
    I5a->push_back(p_fim);
    tabAction.push_back(I5a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I5g;
    I5g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    I5g->push_back(g_E);
    I5g->push_back(g_F);
    I5g->push_back(g_T);
    tabGoto.push_back(I5g);

    // I6
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Shift>(it[5]));
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Error>());
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Shift>(it[4]));
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Error>());
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Error>());
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I6a;
    I6a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I6a->push_back(p_id);
    I6a->push_back(p_mais);
    I6a->push_back(p_estrela);
    I6a->push_back(p_abre);
    I6a->push_back(p_fecha);
    I6a->push_back(p_fim);
    tabAction.push_back(I6a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I6g;
    I6g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int&>(NaoTerminal("T"),it[9]);
    g_F = std::make_pair<NaoTerminal,int&>(NaoTerminal("F"),it[3]);
    I6g->push_back(g_E);
    I6g->push_back(g_F);
    I6g->push_back(g_T);
    tabGoto.push_back(I6g);

    // I7
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Shift>(it[5]));
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Error>());
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Shift>(it[4]));
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Error>());
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Error>());
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I7a;
    I7a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I7a->push_back(p_id);
    I7a->push_back(p_mais);
    I7a->push_back(p_estrela);
    I7a->push_back(p_abre);
    I7a->push_back(p_fecha);
    I7a->push_back(p_fim);
    tabAction.push_back(I7a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I7g;
    I7g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int&>(NaoTerminal("F"),it[10]);
    I7g->push_back(g_E);
    I7g->push_back(g_F);
    I7g->push_back(g_T);
    tabGoto.push_back(I7g);

    // I8
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Shift>(it[6]));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Error>());
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Shift>(it[11]));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Error>());
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I8a;
    I8a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I8a->push_back(p_id);
    I8a->push_back(p_mais);
    I8a->push_back(p_estrela);
    I8a->push_back(p_abre);
    I8a->push_back(p_fecha);
    I8a->push_back(p_fim);
    tabAction.push_back(I8a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I8g;
    I8g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    I8g->push_back(g_E);
    I8g->push_back(g_F);
    I8g->push_back(g_T);
    tabGoto.push_back(I8g);

    // I9
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Reduce>(2));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Shift>(it[7]));
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Reduce>(2));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Reduce>(2));
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I9a;
    I9a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I9a->push_back(p_id);
    I9a->push_back(p_mais);
    I9a->push_back(p_estrela);
    I9a->push_back(p_abre);
    I9a->push_back(p_fecha);
    I9a->push_back(p_fim);
    tabAction.push_back(I9a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I9g;
    I9g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    I9g->push_back(g_E);
    I9g->push_back(g_F);
    I9g->push_back(g_T);
    tabGoto.push_back(I9g);

    // I10
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Reduce>(4));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Reduce>(4));
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Reduce>(4));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Reduce>(4));
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I10a;
    I10a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I10a->push_back(p_id);
    I10a->push_back(p_mais);
    I10a->push_back(p_estrela);
    I10a->push_back(p_abre);
    I10a->push_back(p_fecha);
    I10a->push_back(p_fim);
    tabAction.push_back(I10a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I10g;
    I10g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    I10g->push_back(g_E);
    I10g->push_back(g_F);
    I10g->push_back(g_T);
    tabGoto.push_back(I10g);

    // I11
    p_id = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("id"),std::make_shared<Error>());
    p_mais = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("+"),std::make_shared<Reduce>(6));
    p_estrela = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("*"),std::make_shared<Reduce>(6));
    p_abre = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("("),std::make_shared<Error>());
    p_fecha = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal(")"),std::make_shared<Reduce>(6));
    p_fim = std::make_pair<Terminal,std::shared_ptr<Acao>>
        (Terminal("$"),std::make_shared<Reduce>(6));
    std::shared_ptr<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>> I11a;
    I11a = std::make_shared<std::vector<std::pair<Terminal,std::shared_ptr<Acao>>>>();
    I11a->push_back(p_id);
    I11a->push_back(p_mais);
    I11a->push_back(p_estrela);
    I11a->push_back(p_abre);
    I11a->push_back(p_fecha);
    I11a->push_back(p_fim);
    tabAction.push_back(I11a);
    std::shared_ptr<std::vector<std::pair<NaoTerminal,int>>> I11g;
    I11g = std::make_shared<std::vector<std::pair<NaoTerminal,int>>>();
    g_E = std::make_pair<NaoTerminal,int>(NaoTerminal("E"),-1);
    g_T = std::make_pair<NaoTerminal,int>(NaoTerminal("T"),-1);
    g_F = std::make_pair<NaoTerminal,int>(NaoTerminal("F"),-1);
    I11g->push_back(g_E);
    I11g->push_back(g_F);
    I11g->push_back(g_T);
    tabGoto.push_back(I11g);
    
}

#endif /* ACTION_GOTO_H */
