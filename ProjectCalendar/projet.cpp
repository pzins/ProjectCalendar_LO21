#include "projet.h"

void Projet::ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& description,
                          const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive)
{
    map_tache.insert(std::make_pair(id, new TacheUnitaire(id, titre, description, dispo, echeance, duree, preemptive)));
}


void Projet::ajouterTacheComposite(const QString& id, const QString& titre, const QString& description,
                           const QDate& dispo, const QDate& echeance)
{
    map_tache.insert(std::make_pair(id, new TacheComposite(id, titre, description, dispo, echeance)));
}

void Projet::retirerTache(TacheUnitaire& tache)
{
    //vois cycles de vies liés?
    std::map<QString, Tache*>::iterator it = map_tache.find(tache.getId());
    Tache* tu = (*it).second;
    map_tache.erase(it);
    delete tu;
}

Projet::~Projet()
{
    for(std::map<QString, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}
