#include "precedence.h"
#include "tache.h"
#include "projet.h"

#include <iostream>
QString Precedence::toString() const
{
    QString res = projet->getTitre();
    res += "    antérieure : " +  pred->getTitre();
    res += "    postérieure : " + succ->getTitre();
    return res;
}

bool Precedence::operator==(const Precedence& p)
{
    return  (&p.getPred() == pred && &p.getSucc() == succ && &p.getProjet() == projet);
}


