#ifndef PROJET_H
#define PROJET_H
#include "tachecomposite.h"
#include "observable.h"
#include <QString>
#include <stdexcept>
#include <iostream>
#include "precedencemanager.h"

class Projet : public Observable
{
    //friend class ProjetManager;
private:
    QString titre;
    QString description;
    QDate dispo;
    QDate echeance;
    std::map<QString, Tache*> map_tache;

public:

    Projet(const QString& titre_, const QString& description_, const QDate& dispo_, const QDate& echeance_) :
        titre(titre_), description(description_), dispo(dispo_), echeance(echeance_)
    {
        ajouterObservateur(&PrecedenceManager::getInstance());
    }

    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}
    const QDate& getDispo() const {return dispo;}
    const QDate& getEcheance() const {return echeance;}
    std::map<QString, Tache*>& getMapTache() {return map_tache;}

    void ajouterTache(QChar type, const QString& titre, const QString& description, const QDate& dispo,
                        const QDate& echeance, const Duree& duree, bool preemptive);

    void supprimerTache(QString& titre);

    //verifie avant l'ajout de tache
    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance, const QString& tc_parent);

    //retourne un QString contenant des infos sur le projet
    QString info() const;

    //return un pointeur sur la tache d'après le titre, leve CalendarException sinon elle n'existe pas
    Tache* getTache(const QString& titre);

   ~Projet();//à implémenter pour détruire les taches du projet

    //sauvegarde un les taches du projet
    void save(const QString &titre);
    //charge les taches du projet
    void load(const QString& f);

    bool operator==(const Projet& p);

    void notifier(const QString& str="", const QString& s2="");



    class Iterator
    {
    private:
        std::map<QString, Tache*>::iterator courant;
    public:
        Iterator(std::map<QString, Tache*>::iterator deb) : courant(deb){}
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
