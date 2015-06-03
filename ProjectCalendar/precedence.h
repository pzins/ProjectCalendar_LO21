#ifndef PRECEDENCE_H
#define PRECEDENCE_H
#include <QString>
#include "tache.h"

class Projet;

class Precedence
{
    friend class PrecedenceManager;
private:
    Tache* pred;
    Tache* succ;
    Projet* projet;
    Precedence(Tache& pred_, Tache& succ_, Projet& projet_) : pred(&pred_), succ(&succ_), projet(&projet_){}

public:
    Tache& getPred() const {return *pred;}
    Tache& getSucc() const {return *succ;}
    Projet& getProjet() const {return *projet;}
    QString toString() const;

    bool operator<(const Precedence& p);
    bool operator ==(const Precedence& p);
    bool isInverse(const Precedence& pred) const;
    bool operator==(const Tache& t);
    bool operator==(const Projet& t);

};

#endif // PRECEDENCE_H
