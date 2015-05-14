#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H
#include <QString>
#include "duree.h"
#include "tache.h"

class TacheUnitaire : public Tache
{
    Duree duree;
    bool preemptive;

    TacheUnitaire(const QString& id_, const QString& titre_, const Duree& duree_, const QDate& dispo_,
                  const QDate& echeance_, bool preemptive_=false):
            Tache(id_, titre_, dispo_, echeance_), preemptive(preemptive_){}
    TacheUnitaire(const TacheUnitaire& t);
    TacheUnitaire& operator=(const TacheUnitaire&);
    friend class TacheManager;

public:

    Duree getDuree() const {return duree;}
    void setDuree(const Duree& duree_) {duree=duree_;}


    bool isPreemptive() const {return preemptive;}
    void setPreemptive() {preemptive=true;}
    void setNonPreemptive() {preemptive=false;}

};

#endif // TACHEUNITAIRE_H
