#include "projetmanager.h"

unsigned int ProjetManager::nb_projet = 0;

ProjetManager* ProjetManager::instance = 0;


void ProjetManager::ajouterProjet(const QString& titre, const QDate& dispo,
                                  const QDate& echeance)
{
    map_projet.insert(std::make_pair(nb_projet,new Projet(nb_projet, titre, dispo, echeance)));
    ++nb_projet;
}

void ProjetManager::retirerProjet(Projet &projet)
{
    //a voir cycles vies liés?
    std::map<unsigned int, Projet*>::iterator it = map_projet.find(projet.getId());
    Projet* tu = (*it).second;
    map_projet.erase(it);
    delete tu;
}


Projet& ProjetManager::getProjet(unsigned int id)
{
    return *map_projet.at(id);
}
