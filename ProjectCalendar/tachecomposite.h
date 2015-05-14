#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include <map>
#include "tache.h"
#include "tacheunitaire.h"


class TacheComposite : public Tache
{
private:
    std::map<QString, Tache*> map_tache;

public:

    void ajouterTache(TacheUnitaire& t);
    void retirerTache(TacheUnitaire& t);

    const std::map<QString, Tache*>& getTache() const {return map_tache;}

    TacheComposite(const QString& id_, const QString& titre_, const QString& description_, const QDate& dispo_,
                   const QDate& echeance_):
        Tache(id_, titre_, description_, dispo_, echeance_){}

    virtual void afficher() const;


};

#endif // TACHECOMPOSITE_H
