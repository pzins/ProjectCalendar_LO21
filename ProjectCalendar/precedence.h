#ifndef PRECEDENCE_H
#define PRECEDENCE_H

class Tache;

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
