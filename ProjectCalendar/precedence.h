#ifndef PRECEDENCE_H
#define PRECEDENCE_H
#include <QString>


class Tache;
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

    bool operator <(const Precedence& p);
    bool operator >(const Precedence& p);
    bool operator ==(const Precedence& p);
    bool operator !=(const Precedence& p);

};

#endif // PRECEDENCE_H
