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
    const TacheUnitaire* tache;

public:
    ProgrammationPartieTache(const QDate& date_, const QTime& debut_, const TacheUnitaire& tache_,
                const int numero_, const QString& nom_partie_, const Duree& duree_):
        ProgrammationTacheUnitaire(date_, debut_, tache_), nom_partie(nom_partie_), duree(duree_), tache(&tache_){}
    ~ProgrammationPartieTache();
    virtual void afficher() const
    {
        ProgrammationTacheUnitaire::afficher();
        std::cout << "numero : " << numero << std::endl;
        std::cout << "nom partie : " << nom_partie.toStdString() << std::endl;
        QTextStream a(stdout);
        duree.afficher(a);
    }

};

#endif // PROGRAMMATIONPARTIETACHE_H
