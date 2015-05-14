#include <QCoreApplication>
#include "projetmanager.h"
#include "agenda.h"
#include "precedencemanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProjetManager& projet_m = ProjetManager::getInstance();
    PrecedenceManager& precedence_m = PrecedenceManager::getInstance();
    Agenda& ag = Agenda::getInstance();

    projet_m.ajouterProjet("1","nimpstore",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.ajouterProjet("2","nimpstore",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.ajouterProjet("3","nimpstore",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.ajouterProjet("4","nimpstore",QDate(2012,3,5), QDate(2012,20,6));

    std::cout << projet_m.getMapProjet().size() << std::endl;
    std::cout << projet_m.getProjet("1").getTitre().toStdString() << std::endl;

    projet_m.getProjet("1").ajouterTacheUnitaire("1","tache1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    projet_m.getProjet("1").ajouterTacheComposite("2","tache2","...",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.getProjet("1").ajouterTacheUnitaire("2.1","tache2.1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    projet_m.getProjet("1").ajouterTacheUnitaire("2.2","tache2.2","...",QDate(2012,3,5), QDate(2012,20,6), 5);

    std::cout << projet_m.getProjet("1").getTache("2").getId().toStdString() << std::endl;

    cout << "*************************" << endl;
    for(ProjetManager::Iterator it=projet_m.begin(); it != projet_m.end(); it++) cout << (*it)->getId().toStdString() << endl;

    /* il faut ajouter l'iterator pour les precedences
     * iterator de classe tache permet à partir de getinstance de
     * tacheManager de parcourir les précédences
    */
    return a.exec();
}
