#include "projet.h"

void Projet::ajouterTacheUnitaire(const QString& titre, const QString& description,
                          const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive)
{
    map_tache.insert(std::make_pair(nb_tache, new TacheUnitaire(id, titre, description, dispo, echeance, duree, preemptive)));
    ++nb_tache;
}


void Projet::ajouterTacheComposite(const QString& titre, const QString& description,
                           const QDate& dispo, const QDate& echeance)
{
    map_tache.insert(std::make_pair(nb_tache, new TacheComposite(id, titre, description, dispo, echeance)));
    ++nb_tache;
}

void Projet::retirerTache(TacheUnitaire& tache)
{
    //vois cycles de vies liés?
    std::map<unsigned int, Tache*>::iterator it = map_tache.find(tache.getId());
    Tache* tu = (*it).second;
    map_tache.erase(it);
    delete tu;
}

Projet::~Projet()
{
    for(std::map<unsigned int, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}
