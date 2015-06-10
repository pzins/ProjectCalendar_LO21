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
    virtual const QString& getDescription() const {return tache->getDescription();}


    /**
     * @brief toString : renvoie une QString contenant les informations de la programmation
     * @return
     */
    virtual const QString toString() const;

    /**
     * @brief exportXml : permet l'export d'un programmation en xml
     * @param stream
     */
    virtual void exportXml(QXmlStreamWriter& stream) const;

    /**
     * @brief type : renvoie le type de la programmation
     * 0 : Programmation évènement 1 jour
     * 1 : Programmation rendez-vous
     * 2 : Programmation Tache Unitaire
     * 3 : Programmation Partie de tâche
     * 4 : Programmation évènement plusieurs jours
     */
    virtual const int type() const {return 2;}


};

#endif // PROGRAMMATIONTACHEUNITAIRE_H
