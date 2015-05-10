#ifndef PRECEDENCE_H
#define PRECEDENCE_H
#include "tache.h"

class Precedence
{
private:
    Tache* pred;
    Tache* succ;

public:
    Precedence(Tache& i, Tache& j) : pred(&i), succ(&j){}
    Tache& getPredecesseur() const {return *pred;}
    Tache& getSuccesseur() const {return *succ;}

};

#endif // PRECEDENCE_H
