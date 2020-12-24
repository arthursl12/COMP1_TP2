#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

class Symbol {
    protected:
        std::string symbol;

    public:
        Symbol(){};
        virtual bool isTerminal() = 0;
        
};

class Terminal : public Symbol {
    private:
        bool isVazio;
        bool isFim;
    public:
        Terminal(std::string _symbol);
        bool vazio();
        bool fim();
        virtual bool isTerminal() override;
        friend std::ostream& operator<< (std::ostream &out, const Terminal &t); 
};

class NaoTerminal : public Symbol {
    public:
        NaoTerminal(std::string _symbol);
        virtual bool isTerminal() override;
        friend std::ostream& operator<< (
            std::ostream &out, const NaoTerminal &nt); 

};

#endif /* SYMBOL_H */