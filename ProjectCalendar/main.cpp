#include <QApplication>
#include "projetmanager.h"
#include "agenda.h"
#include "precedencemanager.h"
#include "mainwindow.h"
#include <QTextStream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);/*

    ProjetManager& projet_m = ProjetManager::getInstance();
    PrecedenceManager& precedence_m = PrecedenceManager::getInstance();
    Agenda& ag = Agenda::getInstance();

    projet_m.ajouterProjet("nimpstore",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.ajouterProjet("nimpstore",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.ajouterProjet("nimpstore",QDate(2012,3,5), QDate(2012,20,6));
    projet_m.ajouterProjet("nimpstore",QDate(2012,3,5), QDate(2012,20,6));

    Projet* pro1 = &projet_m.getProjet(1);
    std::cout << projet_m.getMapProjet().size() << std::endl;
    std::cout << pro1->getTitre().toStdString() << std::endl;

    pro1->ajouterTacheUnitaire("tache1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    pro1->ajouterTacheComposite("tache2","...",QDate(2012,3,5), QDate(2012,20,6));
    pro1->ajouterTacheUnitaire("tache2.1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    pro1->ajouterTacheUnitaire("tache2.2","...",QDate(2012,3,5), QDate(2012,20,6), 5);

    std::cout << pro1->getTache(2).getId() << std::endl;

    cout << "*************************" << endl;
    for(ProjetManager::Iterator it=projet_m.begin(); it != projet_m.end(); it++) cout << (*it).getId() << endl;

    for(Projet::Iterator it=pro1->begin(); it != pro1->end(); it++)
        cout << (*it).getTitre().toStdString() << endl;

    precedence_m.ajouterPrecedence(pro1->getTache(0), pro1->getTache(1));
    precedence_m.ajouterPrecedence(pro1->getTache(0), pro1->getTache(2));
    precedence_m.ajouterPrecedence(pro1->getTache(0), pro1->getTache(3));
   std::cout << precedence_m.getVectPrecedence().size() << std::endl;

    cout << "10" << endl;



    for(PrecedenceManager::Iterator it=precedence_m.begin(); it != precedence_m.end(); it++)
        cout << "ol" << endl;

    cout << "10" << endl;

    /* il faut ajouter l'iterator pour les precedences
     * iterator de classe tache permet à partir de getinstance de
     * tacheManager de parcourir les précédences
    */

    MainWindow& m = MainWindow::getInstance();


    m.show();

    return a.exec();
}
