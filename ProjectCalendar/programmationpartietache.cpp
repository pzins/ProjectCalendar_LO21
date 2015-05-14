#include "programmationpartietache.h"


void ProgrammationPartieTache::afficher() const
{
    ProgrammationTacheUnitaire::afficher();
    std::cout << "numero : " << numero << std::endl;
    std::cout << "nom partie : " << nom_partie.toStdString() << std::endl;
    QTextStream a(stdout);
    duree.afficher(a);
}

