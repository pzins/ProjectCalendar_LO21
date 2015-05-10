#include "precedencemanager.h"

PrecedenceManager::PrecedenceManager()
{

}

PrecedenceManager::~PrecedenceManager()
{

}

void PrecedenceManager::ajouterPrecedence(Tache& i, Tache& j)
{
    Precedence* pred = new Precedence(i,j);
    vect_precedence.push_back(pred);
}
