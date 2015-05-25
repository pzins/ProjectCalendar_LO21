#include "tacheunitaire.h"
#include <iostream>

void TacheUnitaire::afficher() const
{
    std::cout << "id: " << getId() << std::endl;
    std::cout << "titre: " << getTitre().toStdString() << std::endl;
    std::cout << "description: " << getDescription().toStdString() << std::endl;
    std::cout << "dispo: " << getDispo().toString().toStdString() << std::endl;
    std::cout << "echeance: " << getEcheance().toString().toStdString() << std::endl;
    std::cout << "duree: " << std::endl;
    QTextStream a(stdout);
    duree.afficher(a);
    std::cout << "preemptive: " << preemptive << std::endl;
}
