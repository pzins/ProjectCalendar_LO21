#include "projetmanager.h"

ProjetManager* ProjetManager::instance = 0;


bool ProjetManager::ajouterProjet(const QString& id, const QString& titre, const QDate& dispo,
                                  const QDate& echeance)
{
    map_projet.insert(std::make_pair(id,new Projet(id, titre, dispo, echeance)));
}


Projet& ProjetManager::getProjet(const QString& id)
{
    return *map_projet.at(id);
}
