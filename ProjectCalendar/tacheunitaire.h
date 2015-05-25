#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H
#include <QString>
#include "duree.h"
#include "tache.h"

class TacheUnitaire : public Tache
{
    Duree duree;
    bool preemptive;


public:

    TacheUnitaire(unsigned int id_, const QString& titre_, const QString& description_, const QDate& dispo_,
                  const QDate& echeance_, const Duree& duree_, bool preemptive_=false):
            Tache(id_, titre_, description_, dispo_, echeance_), duree(duree_), preemptive(preemptive_){}

    TacheUnitaire(const TacheUnitaire& t);
    TacheUnitaire& operator=(const TacheUnitaire&);
    Duree getDuree() const {return duree;}
    void setDuree(const Duree& duree_) {duree=duree_;}


    bool isPreemptive() const {return preemptive;}
    void setPreemptive(bool preemptive_) {preemptive=preemptive_;}
    virtual void afficher(QStandardItem* it);

};

#endif // TACHEUNITAIRE_H
