#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include <map>
#include "tache.h"
#include "tacheunitaire.h"


class TacheComposite : public Tache
{
private:
    std::map<unsigned int, Tache*> map_tache;

public:

    void ajouterTache(Tache& t);
    void retirerTache(Tache& t);

    const std::map<unsigned int, Tache*>& getTache() const {return map_tache;}

    TacheComposite(unsigned int id_, const QString& titre_, const QString& description_, const QDate& dispo_,
                   const QDate& echeance_):
        Tache(id_, titre_, description_, dispo_, echeance_){}
    ~TacheComposite();
    virtual void afficher() const;


};

#endif // TACHECOMPOSITE_H
