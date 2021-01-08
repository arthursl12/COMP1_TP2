#include "utils.h"
#include "tabelas.h"
#include "item.h"
#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

void gramaticaEstendida(Gramatica& g){
    std::vector<std::shared_ptr<Producao>> prods = g.prods;
    NaoTerminal antigoS = prods[0]->label();
    
    std::vector<std::shared_ptr<Symbol>> seq;
    seq.push_back(std::make_shared<NaoTerminal>(antigoS));
    std::shared_ptr<Cadeia> cad = std::make_shared<Cadeia>(seq);
    std::vector<std::shared_ptr<Cadeia>> v;
    v.push_back(cad);

    std::shared_ptr<Producao> newS = \
        std::make_shared<Producao>(NaoTerminal("S\'"),v);
    prods.insert(prods.begin(), newS);
    g = Gramatica(prods);
}

/*
Verifica se um conjunto de ponteiros de Item 'conj' possui pelo menos todas as 
produções do não-terminal 'nt' da gramática 'g'.
*/
bool possuiItemNaoTerminal(std::set<std::shared_ptr<Item>>& conj, 
                           std::shared_ptr<NaoTerminal> nt,
                           Gramatica& g)
{
    // Verifica se possui alguma produção daquele não terminal
    bool possuiTerminal = false;
    for (auto elem : conj){
        if (elem->label() == *nt){
            possuiTerminal = true;
        }
    }
    if (possuiTerminal){
        // Verifica se todas as produções daquele terminal já foram adicionadas
        int qtdCadeias = g.qtdCadeias(nt);
        int itensComNt = 0;
        for (auto elem : conj){
            if (elem->label() == *nt){
                itensComNt++;
            }
        }
        if (itensComNt >= qtdCadeias){
            return true;
        }else{
            return false;
        }    
    }else{
        return false;
    }
}   

/*
Função auxiliar de closure. Adiciona todas as produções do não-terminal 'nt'
em forma de item no conjunto de itens 'conj'
*/
void adicionaProducoes(std::set<std::shared_ptr<Item>>& conj,
                       std::shared_ptr<NaoTerminal>& nt, 
                       Gramatica& g, 
                       bool& adicionou)
{
    // Acha as produções desse não-terminal na gramática
    for(auto prod : g.prods){
        if (prod->label() == *nt){
            for (int i = 0; i < prod->qtdCadeias(); i++){
                // Cria um item para cada cadeia dessa produção
                std::shared_ptr<Item> item = \
                                std::make_shared<Item>((*prod),i);
                conj.insert(item);
                adicionou = true;
            }
        }
    }
}

void closure(std::set<std::shared_ptr<Item>>& conj, Gramatica& g){
    bool adicionou = true;
    // Enquanto for possível adicionar conjuntos
    while(adicionou){
        adicionou = false;
        // Para cada conjunto
        for (auto iter = conj.begin(); iter != conj.end(); iter++){
            Cadeia cad = (**iter).getCadeia();
            std::shared_ptr<Symbol> ponto = std::make_shared<Terminal>(".");
            auto iter1 = cad.find(ponto);
            iter1++;
            if (iter1 == cad.end()){ continue;}
            std::shared_ptr<Symbol> prox = *(iter1++);

            // Continue se for terminal
            if (prox->isTerminal()){ continue;}

            // Explicita o não-terminal
            std::shared_ptr<NaoTerminal> nt = \
                            std::dynamic_pointer_cast<NaoTerminal>(prox);
            
            // Se o que vier depois do ponto não for um terminal (checado acima)
            // E todas as produções daquele não-terminal que ainda 
            // não foram adicionadas
            bool cond1 = possuiItemNaoTerminal(conj,nt,g);
            if ( !cond1 ){
                adicionaProducoes(conj, nt, g, adicionou);
            }
        }
    }
}

void funcaoGoto(std::set<std::shared_ptr<Item>>& in, 
                std::shared_ptr<Symbol>& sym, 
                Gramatica& g,
                std::set<std::shared_ptr<Item>>& out)
{
    for (auto elem : in){
        if (elem->deveAvancar(sym)){
            std::shared_ptr<Item> avancado = std::make_shared<Item>(*elem);
            avancado->avanca();
            
            out.insert(avancado);
            closure(out, g);
        }
    }
}

/*
Calcula os Conjuntos de Conjuntos de Itens (Estados do AF) para a gramática 
aumentada g
*/
void conjuntosItens(ConjuntoItens& conjs, Gramatica& g){
    // C = closure({S'->S})
    std::shared_ptr<Item> it0 = std::make_shared<Item>(g.getInicial());
    std::set<std::shared_ptr<Item>> closureS;
    closureS.insert(it0);
    closure(closureS, g);
    conjs.insert(closureS);

    // Determina o conjunto de símbolos da gramática (terminais e não-terminais)
    std::set<NaoTerminal> nts;
    g.conjuntoNaoTerminais(nts);
    std::set<Terminal> tts;
    g.conjuntoTerminais(tts);

    std::set<std::shared_ptr<Symbol>> symbs;
    for (NaoTerminal nt: nts){
        std::shared_ptr<Symbol> sym = std::make_shared<NaoTerminal>(nt);
        symbs.insert(sym);
    }
    for (Terminal t: tts){
        std::shared_ptr<Symbol> sym = std::make_shared<Terminal>(t);
        symbs.insert(sym);
    }

    // Loop principal
    bool adicionou = true;
    while(adicionou){
        adicionou = false;
        // Para cada conjunto
        for (auto it = conjs.begin(); it != conjs.end(); it++){
            Elemento el = (**it);
            std::set<std::shared_ptr<Item>> c1 = el.conj_item;
            // Para cada símbolo da gramática
            for (auto sym: symbs){
                std::set<std::shared_ptr<Item>> out;
                out.clear();

                funcaoGoto(c1, sym, g, out);

                auto find = conjs.find(out);
                if (find == conjs.end() && out.size() > 0){
                    conjs.insert(out);
                    adicionou = true;
                }
            }
            
        }
    }
}

/*
Lê o arquivo 'filename' e coloca cada linha (cada programa) em uma posição do
vector de strings informado
*/
void inputFile(std::vector<std::string>& programas, std::string filename){
    std::ifstream infile(filename);
    if (!infile.is_open()) throw "Problema na abertura do arquivo";

    std::string line;
    programas.clear();
    // Lê o arquivo linha por linha
    while (std::getline(infile, line)){
        if (line[0] == '#' ||  line.size() == 0){
            // Linhas começando com '#' são comentários
            continue;
        }
        programas.push_back(line);
    }
}

void outputTables(Gramatica& g, std::string filename){
    std::cout << "Imprimindo tabelas e estados no arquivo ";
    std::cout << filename << std::endl;

    std::ofstream out(filename);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!


    TabelaAction t1;
    TabelaGoto t2;
    tabActionGoto(t1, t2, g, true);

    std::cout.rdbuf(coutbuf); //reset to standard output again

}


void inputId(std::string& out, std::string idName){
    bool isValid = false;
    std::string in;
    while (!isValid){
        std::cout << "Valor de <" << idName << ">: ";
        std::getline(std::cin, in);

        if (in == "true" || in == "false"){
            out = in;
            isValid = true;
            break;
        }

        try{
            std::stoi(in);
            out = in;
            break;
        }catch(std::exception& e){
            try{
                std::stof(in);
                out = in;
                break;
            }catch(std::exception& e){
                continue;
            }
        }
    }
}



