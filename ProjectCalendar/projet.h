#ifndef PROJET_H
#define PROJET_H
#include "tache.h"
#include "tacheunitaire.h"
#include "tachecomposite.h"
#include <QString>

class Projet
{
    friend class ProjetManager;
private:
    QString id;
    QString titre;
    QDate dispo;
    QDate echeance;
    std::map<QString, Tache*> map_tache;

public:
    Projet(const QString& id_, const QString& titre_, const QDate& dispo_, const QDate& echeance_) :
        id(id_), titre(titre_), dispo(dispo_), echeance(echeance_){}

    const QString& getId() const {return id;}
    const QString& getTitre() const {return titre;}
    const QDate& getDispo() const {return dispo;}
    const QDate& getEcheance() const {return echeance;}

    void ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& description,
                              const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive=false);
    void ajouterTacheComposite(const QString& id, const QString& titre, const QString& description,
                               const QDate& dispo, const QDate& echeance);
    void retirerTache(const QString& id);

    const std::map<QString, Tache*>& getMapTache() const {return map_tache;}

    Tache& getTache(const QString& id){
        return *map_tache.at(id);
    }
   ~Projet(){}

    class Iterator
    {
    private:
        friend class Projet;
        std::map<QString, Tache*>::iterator courant;
        Iterator(std::map<QString, Tache*>::iterator deb) : courant(deb){}
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

#endif // PROJET_H
