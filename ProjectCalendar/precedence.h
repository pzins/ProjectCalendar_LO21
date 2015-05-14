#ifndef PRECEDENCE_H
#define PRECEDENCE_H
#include "tache.h"

class Precedence
{
    friend class PrecedenceManager;
private:
    Tache* pred;
    Tache* succ;
    Precedence(Tache& pred_, Tache& succ_) : pred(&pred_), succ(&succ_){}

public:
    Tache& getPred() const {return *pred;}
    Tache& getSucc() const {return *succ;}

};

#endif // PRECEDENCE_H
