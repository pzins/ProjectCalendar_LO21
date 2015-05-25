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
    virtual void afficher(QStandardItem* it) ;

    class Iterator
    {
        friend class TacheComposite;
        std::map<unsigned int, Tache*>::iterator courant;
        Iterator(std::map<unsigned int, Tache*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0){}
        Tache& operator*() const {return *(courant->second);}
        Iterator& operator++(){++courant; return *this;}
        Iterator operator++(int i){
            Iterator old = *this;
            ++courant;
            return old;
        }
        bool operator==(Iterator it) const{
            return courant == it.courant;
        }
        bool operator!=(Iterator it) const{
            return courant != it.courant;
        }
    };
    Iterator begin(){return Iterator(map_tache.begin());}
    Iterator end(){return Iterator(map_tache.end());}
};




#endif // TACHECOMPOSITE_H
