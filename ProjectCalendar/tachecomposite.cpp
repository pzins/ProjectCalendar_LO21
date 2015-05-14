#include "tachecomposite.h"
#include <iostream>

void TacheComposite::ajouterTache(TacheUnitaire& t)
{
    map_tache.insert(std::make_pair(t.getId(), &t));
}

void TacheComposite::retirerTache(TacheUnitaire& t)
{
    //à voir en fct de si suppr tache ou juste enlève de cette tachecompo
    //voir cycles de vies liés ou pas
}

void TacheComposite::afficher() const
{
    std::cout << "id: " << getId().toStdString() << std::endl;
    std::cout << "titre: " << getTitre().toStdString() << std::endl;
    std::cout << "description: " << getDescription().toStdString() << std::endl;
    std::cout << "dispo: " << getDispo().toString().toStdString() << std::endl;
    std::cout << "echeance: " << getEcheance().toString().toStdString() << std::endl;
    std::cout << "tache contenues: " << std::endl;
    for (std::map<QString, Tache*>::const_iterator it=map_tache.begin(); it!=map_tache.end(); ++it)
    {
        it->second->afficher();
    }
}

