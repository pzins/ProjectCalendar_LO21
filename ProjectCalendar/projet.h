#ifndef PROJET_H
#define PROJET_H
#include "tachecomposite.h"
#include "observable.h"
#include <QString>
#include <stdexcept>
#include <iostream>
#include "precedencemanager.h"

/**
 * @class Projet
 * @brief Classe représentant un projet
 */
class Projet : public Observable
{
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

    /**
     * @brief ajouterTache : ajout d'une tache à un projet
     * @param type
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     * @param duree
     * @param preemptive
     */
    void ajouterTache(QChar type, const QString& titre, const QString& description, const QDate& dispo,
                        const QDate& echeance, const Duree& duree, bool preemptive);

    /**
     * @brief supprimerTache : suppression d'une tache d'un projet
     * @param titre
     */
    void supprimerTache(QString& titre);

    /**
     * @brief verification : vérification des contraintes liées à l'ajout de taches dans un projet
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     * @param tc_parent
     */
    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance, const QString& tc_parent);

    //****//
    QString info() const;

    /**
     * @brief getTache : renvoie un pointeur sur une tache, à partir du nom de cette tache
     * @param titre
     */
    Tache* getTache(const QString& titre);

   ~Projet();


    void save(const QString &titre);
    void load(const QString& f);

    /**
     * @brief operator == : compare 2 projets (par rapport à leurs titre)
     * @param p
     */
    bool operator==(const Projet& p);


    void notifier(const QString& str="", const QString& s2="");


    /**
     * @class Iterator
     * @brief Iterator de projet qui parcourt les taches du projet
     */
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
