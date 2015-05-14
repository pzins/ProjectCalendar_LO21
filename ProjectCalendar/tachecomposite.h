#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include <map>
#include "tache.h"


class TacheComposite : public Tache
{
private:
    std::map<QString, Tache*> vect_tache;

public:

    //void ajouterTache(Tache& t){vect_tache[t.getId()] = t;}

    const std::map<QString, Tache*>& getTache() const {return vect_tache;}

    TacheComposite(const QString& id_, const QString& titre_, const QDate& dispo_, const QDate& echeance_):
        Tache(id_, titre_, dispo_, echeance_){}


};

#endif // TACHECOMPOSITE_H
