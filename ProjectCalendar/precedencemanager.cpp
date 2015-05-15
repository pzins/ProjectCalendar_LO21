#include "precedencemanager.h"

PrecedenceManager* PrecedenceManager::instance = 0;

void PrecedenceManager::ajouterPrecedence(Tache &pred_, Tache &succ_)
{
    Precedence* pred = new Precedence(pred_,succ_);
    vect_precedence.push_back(pred);
}


PrecedenceManager::~PrecedenceManager()
{
    for(std::vector<Precedence*>::iterator it=vect_precedence.begin(); it != vect_precedence.end(); ++it)
        delete *it;
}

void PrecedenceManager::retirerPrecedence(Precedence& precedence)
{
    for(std::vector<Precedence*>::iterator it = vect_precedence.begin(); it != vect_precedence.end(); ++it)
        if(&precedence == *it)
        {
            vect_precedence.erase(it);
            break;
        }
}
