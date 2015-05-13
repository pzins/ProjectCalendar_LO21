#include <iostream>
#include "programmationrdv.h"

void ProgrammationRdv::ajouterPersonne(const QString& nom)
{
    for (std::vector<QString>::iterator it = personne.begin() ; it != personne.end(); ++it)
    {
        if(*it == nom){
            std::cout << "Cette Personne existe déjà" << std::endl;
            break;
        }
    }
    personne.push_back(nom);
}


void ProgrammationRdv::retirerPersonne(const QString& nom)
{
    for (std::vector<QString>::iterator it = personne.begin() ; it != personne.end(); ++it)
    {
        if(*it == nom){
            personne.erase(it);
            break;
        }
    }
    std::cout << "Cette personne n'existe pas" << std::endl;

}
