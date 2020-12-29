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
        int estado_j;
    public:
        Shift(int _estado_j);
        virtual std::string getTipo() override;
        friend std::ostream& operator<< (std::ostream &out, const Shift& sh); 

};

class Reduce : public Acao{
    protected:
        int prod_i;
    public:
        Reduce(int _prod_i);
        virtual std::string getTipo() override;
        friend std::ostream& operator<< (std::ostream &out, const Reduce& re); 
};


#endif /* ACTION_H */
