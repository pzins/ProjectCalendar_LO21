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

    TacheUnitaire(const QString& titre_, const QString& description_, const QDate& dispo_,
                  const QDate& echeance_, const Duree& duree_, bool preemptive_=false):
            Tache(titre_, description_, dispo_, echeance_), duree(duree_), preemptive(preemptive_){}

    TacheUnitaire(const TacheUnitaire& t);
    TacheUnitaire& operator=(const TacheUnitaire&);
    Duree getDuree() const {return duree;}
    void setDuree(const Duree& duree_) {duree=duree_;}
    virtual void exportXml(QXmlStreamWriter& stream);

    bool isPreemptive() const {return preemptive;}
    void setPreemptive(bool preemptive_) {preemptive=preemptive_;}
    virtual bool isComposite() const {return false;}
    virtual QString info() const;

};

#endif // TACHEUNITAIRE_H
