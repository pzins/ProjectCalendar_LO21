#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "duree.h"
#include "tache.h"


/**
 * @class TacheUnitaire
 * @brief Classe abstraite représentant une TacheUnitaire
 */
class TacheUnitaire : public Tache
{
    Duree duree;
    bool preemptive;
    bool programmed;


public:

    TacheUnitaire(const QString& titre_, const QString& description_, const QDate& dispo_,
                  const QDate& echeance_, const Duree& duree_, bool preemptive_=false):
            Tache(titre_, description_, dispo_, echeance_), duree(duree_),
            preemptive(preemptive_), programmed(false) {  }

    virtual ~TacheUnitaire();

    Duree getDuree() const {return duree;}
    void setDuree(const Duree& duree_) {duree=duree_;}


    virtual void exportXml(QXmlStreamWriter& stream) const;

    bool isProgrammed() const {return programmed;}
    void setIsProgrammed(bool b) {programmed= b;}

    bool isPreemptive() const {return preemptive;}
    void setPreemptive(bool preemptive_) {preemptive=preemptive_;}
    virtual bool isComposite() const {return false;}
    virtual const QString info() const;

};

#endif // TACHEUNITAIRE_H
