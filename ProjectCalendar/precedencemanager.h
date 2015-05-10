#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include "precedence.h"

class PrecedenceManager
{
private:
    std::vector<Precedence*> vect_precedence;
public:
    PrecedenceManager();
    ~PrecedenceManager();
    void ajouterPrecedence(Tache& i, Tache& j);
};

#endif // PRECEDENCEMANAGER_H
