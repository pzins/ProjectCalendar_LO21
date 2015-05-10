#include "precedencemanager.h"



void PrecedenceManager::ajouterPrecedence(Tache& i, Tache& j)
{
    Precedence* pred = new Precedence(i,j);
    vect_precedence.push_back(pred);
}
