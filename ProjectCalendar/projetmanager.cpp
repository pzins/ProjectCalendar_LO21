#include "projetmanager.h"

ProjetManager* ProjetManager::instance = 0;


bool ProjetManager::ajouterProjet(const QString& id, const QString& titre, const QDate& dispo,
                                  const QDate& echeance)
{
    map_projet.insert(std::make_pair(id,new Projet(id, titre, dispo, echeance)));
}

void ProjetManager::retirerProjet(Projet &projet)
{
    //a voir cycles vies liés?
    std::map<QString, Projet*>::iterator it = map_projet.find(projet.getId());
    Projet* tu = (*it).second;
    map_projet.erase(it);
    delete tu;
}


Projet& ProjetManager::getProjet(const QString& id)
{
    return *map_projet.at(id);
}
