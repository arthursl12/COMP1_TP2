#ifndef ACTION_H
#define ACTION_H

#include "symbol.h"
#include <string>

class Acao{
    protected:
        std::string tipo;
    public:
        Acao();
        virtual std::string getTipo() = 0;
};

class Accept : public Acao{
    public:
        Accept();
        virtual std::string getTipo() override;
        friend std::ostream& operator<< (std::ostream &out, const Accept& ac); 
};

class Error : public Acao{
    public:
        Error();
        virtual std::string getTipo() override;
        friend std::ostream& operator<< (std::ostream &out, const Error& er); 

};

class Shift : public Acao{
    protected:
        int j;
    public:
        Shift(int _j);
        virtual std::string getTipo() override;
        friend std::ostream& operator<< (std::ostream &out, const Shift& sh); 

};

class Reduce : public Acao{
    protected:
        NaoTerminal A;
        Terminal alpha;
    public:
        Reduce(NaoTerminal _A, Terminal _alpha);
        virtual std::string getTipo() override;
        friend std::ostream& operator<< (std::ostream &out, const Reduce& re); 
};


#endif /* ACTION_H */
