#include "precedencemanager.h"
#include "calendarexception.h"
#include "projetmanager.h"
#include <iostream>


PrecedenceManager* PrecedenceManager::instance = 0;


PrecedenceManager::~PrecedenceManager()
{
    for(std::set<Precedence*, MyComp>::iterator it = set_precedence.begin(); it != set_precedence.end(); ++it)
        delete (*it);
}


void PrecedenceManager::ajouterPrecedence(Tache &pred_, Tache &succ_, Projet& projet_)
{
    Precedence* pred = new Precedence(pred_,succ_, projet_);
    if(!set_precedence.insert(pred).second)
    {
        delete pred;
        throw CalendarException("Précédence déjà présente");
    }
    else if (containsInverse(*pred))
    {
        delete pred;
        throw CalendarException("Précédence non cohérente");
    }
    else
    {
        notifier();
    }
}

bool PrecedenceManager::containsInverse(const Precedence &p) const
{
    for(PrecedenceManager::ConstIterator it = begin(); it != end(); ++it)
    {
        if(p.isInverse(*it))
            return true;
    }
    return false;
}

/*
bool PrecedenceManager::contains(const Precedence& p)
{
    for(Iterator it = begin(); it != end(); ++it)
    {
        if((*it) == p){
            return true;
        }
    }
    return false;
}*/

void PrecedenceManager::retirerPrecedence(Precedence &p)
{
    for(std::set<Precedence*, MyComp>::iterator it = set_precedence.begin(); it != set_precedence.end(); ++it)
    {
        std::cout << "ok" << std::endl;
        if(p == *(*it))
        {
            std::cout << "klm" << std::endl;
            set_precedence.erase(it);
            notifier();
            break;
        }
    }
}

std::vector<Precedence*> PrecedenceManager::findPrecedence(Projet* p, Tache* t)
{
    std::vector<Precedence*> vec;
    if(p)
    {
        for(PrecedenceManager::Iterator it = begin(); it != end(); ++it)
        {
            if((*it) == *p && ((*it) == *t) || !t)
            {
                vec.push_back(&*it);
            }
        }
    }
    return vec;
}

void PrecedenceManager::update(const QString& s1, const QString& s2)
{
    std::cout << "ol" << std::endl;
    Projet* p = ProjetManager::getInstance().getProjet(s1);
    if(!p) return;
    Tache* t = p->getTache(s2);
    std::vector<Precedence*> vec = findPrecedence(p, t);
    std::cout << "ollo " << vec.size() << std::endl;
    for(std::vector<Precedence*>::iterator it = vec.begin(); it != vec.end(); ++it)
         retirerPrecedence(*(*it));
}

void PrecedenceManager::notifier(const QString& s1, const QString& s2)
{
    for(Observable::Iterator it = getObs().begin(); it != getObs().end(); ++it)
        (*it).update(s1,s2);
}
