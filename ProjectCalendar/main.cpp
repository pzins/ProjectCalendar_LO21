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

    Projet* pro1 = &projet_m.getProjet("1");
    std::cout << projet_m.getMapProjet().size() << std::endl;
    std::cout << pro1->getTitre().toStdString() << std::endl;

    pro1->ajouterTacheUnitaire("1","tache1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    pro1->ajouterTacheComposite("2","tache2","...",QDate(2012,3,5), QDate(2012,20,6));
    pro1->ajouterTacheUnitaire("2.1","tache2.1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    pro1->ajouterTacheUnitaire("2.2","tache2.2","...",QDate(2012,3,5), QDate(2012,20,6), 5);

    std::cout << pro1->getTache("2").getId().toStdString() << std::endl;

    cout << "*************************" << endl;
    for(ProjetManager::Iterator it=projet_m.begin(); it != projet_m.end(); it++) cout << (*it).getId().toStdString() << endl;

    for(Projet::Iterator it=pro1->begin(); it != pro1->end(); it++)
        cout << (*it).getTitre().toStdString() << endl;

    precedence_m.ajouterPrecedence(pro1->getTache("1"), pro1->getTache("2"));
    precedence_m.ajouterPrecedence(pro1->getTache("1"), pro1->getTache("2.1"));
    precedence_m.ajouterPrecedence(pro1->getTache("1"), pro1->getTache("2.2"));
    std::cout << precedence_m.getVectPrecedence().size() << std::endl;

    cout << "10" << endl;



    for(PrecedenceManager::Iterator it=precedence_m.begin(); it != precedence_m.end(); it++)
        cout << "ol" << endl;

    cout << "10" << endl;


    /* il faut ajouter l'iterator pour les precedences
     * iterator de classe tache permet à partir de getinstance de
     * tacheManager de parcourir les précédences
    */
    return a.exec();
}
