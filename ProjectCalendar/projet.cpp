#include "projet.h"

void Projet::ajouterTacheUnitaire(const QString& titre, const QString& description,
                          const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive)
{
    map_tache.insert(std::make_pair(titre, new TacheUnitaire(id, titre, description, dispo, echeance, duree, preemptive)));
    ++nb_tache;
}


void Projet::ajouterTacheComposite(const QString& titre, const QString& description,
                           const QDate& dispo, const QDate& echeance)
{
    map_tache.insert(std::make_pair(titre, new TacheComposite(id, titre, description, dispo, echeance)));
    ++nb_tache;
}

void Projet::retirerTache(QString& titre)
{
    //vois cycles de vies liés?
   /* std::map<QString, Tache*>::iterator it = map_tache.find(titre);
    Tache* tu = (*it).second;
    map_tache.erase(it);
    delete tu;
    nb_tache--;
    map_tache.at(nb_tache)->setId(tache.getId());*/
}

Projet::~Projet()
{
    for(std::map<QString, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}
