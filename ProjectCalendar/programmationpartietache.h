#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H
#include "programmationtacheunitaire.h"
#include "duree.h"
#include <QString>

class ProgrammationPartieTache : public ProgrammationTacheUnitaire
{
private:
    int numero;
    QString nom_partie;
    Duree duree;

public:
    ProgrammationPartieTache(const QDate& date_, const QTime& debut_, TacheUnitaire& tache_,
                const int numero_, const QString& nom_partie_, const Duree& duree_, const QString& projet_):
        ProgrammationTacheUnitaire(date_, debut_, tache_, projet_), nom_partie(nom_partie_),
        numero(numero_), duree(duree_){}


    virtual ~ProgrammationPartieTache(){}
    virtual void afficher() const;
    virtual const Duree& getDuree() const {return duree;}
    const QString getNomPartie() const {return nom_partie;}
    int getNumero() const {return numero;}
    virtual bool isTache() const {return true;}
    virtual void exportXml(QXmlStreamWriter& stream) const;

};

#endif // PROGRAMMATIONPARTIETACHE_H
