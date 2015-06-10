#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H
#include "programmationtacheunitaire.h"

/**
 * @class ProgrammationPartieTache
 * @brief Classe représentant la programmation d'une partie d'une tache
 */
class ProgrammationPartieTache : public ProgrammationTacheUnitaire
{
private:
    int numero;
    QString nom_partie;
    Duree duree;

public:
    /**
     * @brief ProgrammationPartieTache
     * @param date_ date de début
     * @param debut_ horaire de début
     * @param tache_ tache concernée
     * @param numero_ numéro de ma partie
     * @param nom_partie_ nom de la partie
     * @param duree_ durée de la partie
     * @param projet_ nom du projet concerné
     */
    ProgrammationPartieTache(const QDate& date_, const QTime& debut_, TacheUnitaire& tache_,
                const int numero_, const QString& nom_partie_, const Duree& duree_, Projet& projet_):
        ProgrammationTacheUnitaire(date_, debut_, tache_, projet_), nom_partie(nom_partie_),
        numero(numero_), duree(duree_){}


    virtual const Duree& getDuree() const {return duree;}
    const QString getNomPartie() const {return nom_partie;}
    const int getNumero() const {return numero;}

    /**
     * @brief exportXml : exporte une tache en XML
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
    virtual const int type() const {return 3;}

    /**
     * @brief toString : renvoie un QString contenant les informations de la programmation
     * @return
     */
    virtual const QString toString() const;
};

#endif // PROGRAMMATIONPARTIETACHE_H
