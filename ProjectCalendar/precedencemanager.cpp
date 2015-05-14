#include "precedencemanager.h"

PrecedenceManager* PrecedenceManager::instance = 0;

void PrecedenceManager::ajouterPrecedence(Tache &pred_, Tache &succ_)
{
    Precedence* pred = new Precedence(pred_,succ_);
    vect_precedence.push_back(pred);
}
