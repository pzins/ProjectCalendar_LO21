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



    ~Projet();
};

#endif // PROJET_H
