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
    //ProjetManager::Iterator it = map_projet.find(projet.getId());
    //Projet* tu = (*it).second;
    //map_projet.erase(it);
    //delete tu;
    nb_projet--;
    map_projet.at(nb_projet)->setId(projet.getId());
}


Projet& ProjetManager::getProjet(unsigned int id)
{
    return *map_projet.at(id);
}


void ProjetManager::remplirModel()
{
    model.clear();
    for(ProjetManager::Iterator it = begin(); it != end(); ++it)
    {
        QStandardItem* item = new QStandardItem((*it).getTitre());
        model.appendRow(item);
        for(Projet::Iterator ite = (*it).begin(); ite != (*it).end(); ++ite)
        {
           (*ite).afficher(item);
        }
    }
}
