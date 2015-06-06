#ifndef PROGRAMMATIONTACHEUNITAIRE_H
#define PROGRAMMATIONTACHEUNITAIRE_H
#include "programmation.h"
#include "tacheunitaire.h"

class ProgrammationTacheUnitaire : public Programmation
{
private:
    const TacheUnitaire* tache;

public:
    ProgrammationTacheUnitaire(const QDate date_, const QTime& debut_, const TacheUnitaire& tache_):
        Programmation(date_, debut_), tache(&tache_){}

    virtual ~ProgrammationTacheUnitaire(){}

    const TacheUnitaire* getTache() const {return tache;}

    virtual void afficher() const;
    virtual const Duree& getDuree() const {return tache->getDuree();}
    virtual const QString& getTitre() const {return tache->getTitre();}
    virtual bool isEvtPlsJ() const {return false;}

};

#endif // PROGRAMMATIONTACHEUNITAIRE_H
