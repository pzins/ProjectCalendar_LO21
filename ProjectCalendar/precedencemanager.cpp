#include "precedencemanager.h"
#include <iostream>

PrecedenceManager* PrecedenceManager::instance = 0;


PrecedenceManager::~PrecedenceManager()
{
    for(std::set<Precedence*>::iterator it = set_precedence.begin(); it != set_precedence.end(); ++it)
        delete (*it);
}


void PrecedenceManager::ajouterPrecedence(Tache &pred_, Tache &succ_, Projet& projet_)
{
    Precedence* pred = new Precedence(pred_,succ_, projet_);
    if(!contains(*pred))
    {
        set_precedence.insert(pred);
        notifier();
    }
}

bool PrecedenceManager::contains(const Precedence& p)
{
    for(Iterator it = begin(); it != end(); ++it)
    {
        if((*it) == p){
            return true;
        }
    }
    return false;
}


void PrecedenceManager::retirerPrecedence(Precedence& precedence)
{
    for(std::set<Precedence*> ::iterator it = set_precedence.begin(); it != set_precedence.end(); ++it)
    {
        if(&precedence == *it)
        {
            set_precedence.erase(it);
            notifier();
            break;
        }
    }
}

void PrecedenceManager::notifier()
{
    for(std::set<Observateur*>::iterator it = obs.begin(); it != obs.end(); ++it)
        (*it)->update();
}
void PrecedenceManager::ajouterObservateur(Observateur* o)
{
    obs.insert(o);
}

void PrecedenceManager::supprimerObservateur(Observateur* o)
{
    obs.erase(o);
}
