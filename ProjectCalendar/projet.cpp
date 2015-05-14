#include "projet.h"

bool Projet::ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& description,
                          const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive)
{
    map_tache.insert(std::make_pair(id, new TacheUnitaire(id, titre, description, dispo, echeance, duree, preemptive)));
}


bool Projet::ajouterTacheComposite(const QString& id, const QString& titre, const QString& description,
                           const QDate& dispo, const QDate& echeance)
{
    map_tache.insert(std::make_pair(id, new TacheComposite(id, titre, description, dispo, echeance)));
}
