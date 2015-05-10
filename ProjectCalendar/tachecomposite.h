#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include "tache.h"

class TacheComposite : public Tache
{
private:
    QString titre;
    std::map<QString, Tache*> vect_tache;


public:

    void ajouterTache(Tache& t){vect_tache[t.getId()] = t;}

    virtual QString getTitre() const {return titre;}
    virtual QString getId() const{return "ol";}
    virtual std::map<QString, Tache*> getTache(){return vect_tache;}
    TacheComposite();
    ~TacheComposite();


};

#endif // TACHECOMPOSITE_H
