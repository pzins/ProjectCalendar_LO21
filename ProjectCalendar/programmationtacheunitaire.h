#ifndef PROGRAMMATIONTACHEUNITAIRE_H
#define PROGRAMMATIONTACHEUNITAIRE_H
#include "programmation.h"
#include "projet.h"

class TacheUnitaire;

/**
 * @class ProgrammationPartieTache
 * @brief Classe représentant la programmation d'une tache unitaire d'un projet
 */
class ProgrammationTacheUnitaire : public Programmation
{
private:
    TacheUnitaire* tache;
    Projet* projet;

public:
    /**
     * @brief ProgrammationTacheUnitaire
     * @param date_ date de début
     * @param debut_ horaire de début
     * @param tache_ tache concernée
     * @param projet_ nom du projet concerné
     */
    ProgrammationTacheUnitaire(const QDate date_, const QTime& debut_, TacheUnitaire& tache_, Projet& projet_):
        Programmation(date_, debut_), tache(&tache_), projet(&projet_){}

    TacheUnitaire* getTache() const {return tache;}
    Projet* getProjet() const {return projet;}

    virtual const Duree& getDuree() const {return tache->getDuree();}
    virtual const QString& getTitre() const {return tache->getTitre();}
    virtual bool isEvtPlsJ() const {return false;}
    virtual bool isTache() const {return true;}

    virtual const QString toString() const;
    virtual const QString& getDescription() const {return tache->getDescription();}
    virtual void exportXml(QXmlStreamWriter& stream) const;
    virtual const int type() const {return 2;}


};

#endif // PROGRAMMATIONTACHEUNITAIRE_H
