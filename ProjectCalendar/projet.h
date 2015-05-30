#ifndef PROJET_H
#define PROJET_H
#include "tache.h"
#include "tacheunitaire.h"
#include "tachecomposite.h"
#include <QString>
#include <stdexcept>
#include <iostream>

class Projet
{
    friend class ProjetManager;
private:
    QString titre;
    QString description;
    QDate dispo;
    QDate echeance;
    unsigned int nb_tache;
    std::map<QString, Tache*> map_tache;

public:

    Projet(const QString& titre_, const QString& description_, const QDate& dispo_, const QDate& echeance_) :
        titre(titre_), description(description_), dispo(dispo_), echeance(echeance_){}

    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}
    const QDate& getDispo() const {return dispo;}
    const QDate& getEcheance() const {return echeance;}

    void ajouterTache(QChar type, const QString& titre, const QString& description, const QDate& dispo,
                        const QDate& echeance, const Duree& duree, bool preemptive);

    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance, const QString& tc_parent)
    {
        std::map<QString, Tache*>::iterator it = map_tache.find(tc_parent);
        if(it != map_tache.end())
        {
            if((*it).second->getDispo() > dispo) throw CalendarException("Disponibilité et disponibilité de tache mère sont incohérentes");
            if((*it).second->getEcheance() < echeance) throw CalendarException("Echéance et échéance de tache mère sont incohérentes");
        }
        if(titre == "") throw CalendarException("Veuillez entrer un titre");
        if(map_tache.find(titre) != map_tache.end()) throw CalendarException("Titre déjà attribué");
        if(map_tache.find(titre) != map_tache.end()) throw CalendarException("Titre déjà attribué");
        if(description == "") throw CalendarException("Veuillez entrer une description");
        if(echeance > this->echeance) throw CalendarException("Echéance et échéance du projet sont incohérentes");
        if(dispo < this->dispo) throw CalendarException("Disponibilité et disponibilité du projet sont incohérentes");
        if(dispo > echeance) throw CalendarException("Disponibilité et échéance sont incohérentes");
    }

    void supprimerTache(QString& titre);

    std::map<QString, Tache*>& getMapTache() {return map_tache;}

    Tache* getTache(const QString& titre)
    {
        try
        {
            return map_tache.at(titre);
        }
        catch(out_of_range)
        {
            return 0;
        }
    }

   ~Projet();

    void save(const QString &titre);
    void load(const QString& f);




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
