#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include "precedence.h"

class PrecedenceManager
{
private:
    std::vector<Precedence*> vect_precedence;
    PrecedenceManager(){}
    ~PrecedenceManager(){}
    PrecedenceManager(const PrecedenceManager& p){}
    PrecedenceManager& operator=(const PrecedenceManager& p){}

    static PrecedenceManager* instance;


public:
    void ajouterPrecedence(Tache& i, Tache& j);
    static PrecedenceManager& getInstance(){
        if(!instance) instance = new PrecedenceManager();
        return *instance;
    }

    static void liberer_instance(){
        delete instance;
    }
};

#endif // PRECEDENCEMANAGER_H
