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
                const int numero_, const QString& nom_partie_, const Duree& duree_, const QString& projet_):
        ProgrammationTacheUnitaire(date_, debut_, tache_, projet_), nom_partie(nom_partie_),
        numero(numero_), duree(duree_){}


    virtual const Duree& getDuree() const {return duree;}
    const QString getNomPartie() const {return nom_partie;}
    int getNumero() const {return numero;}
    virtual bool isTache() const {return true;}
    virtual void exportXml(QXmlStreamWriter& stream) const;

    virtual const QString toString() const;
    virtual const int type() const {return 3;}
};

#endif // PROGRAMMATIONPARTIETACHE_H
