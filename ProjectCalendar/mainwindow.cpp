#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow* MainWindow::instance = 0;

MainWindow& MainWindow::getInstance(QWidget* parent)
{
    if(instance) return *instance;
    else{
        instance = new MainWindow(parent);
        return *instance;
    }
}

void MainWindow::libererInstance()
{
    delete instance;
    instance = 0;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pm = &ProjetManager::getInstance();

    pm->ajouterProjet("ol",QDate(2000,5,6),QDate(2003,2,5));
    pm->ajouterProjet("lyon",QDate(2000,5,6),QDate(2003,2,5));
    Projet* pro1 = &(pm->getProjet(0));

    pro1->ajouterTacheUnitaire("tache1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    pro1->ajouterTacheComposite("tache2","...",QDate(2012,3,5), QDate(2012,20,6));

    Tache* u = new TacheUnitaire(17,"tache3","...",QDate(2012,3,5), QDate(2012,20,6), 5);

    TacheComposite* c = dynamic_cast<TacheComposite*>(&pro1->getTache(1));
    c->ajouterTache(*u);

    ag = &Agenda::getInstance();
    //model_tree = new QStandardItemModel(5,3);
    /*
    QStandardItem* item = new QStandardItem("nabil fekir");
    model_tree->appendRow(item);
    item->appendRow(new QStandardItem("21 ans"));*/
    pm->remplirModel();
    //afficher_projets(pm->getModel());
    ui->treeView->setModel(&pm->getModel());
    connect(ui->nouveau_projet, SIGNAL(clicked()),this,SLOT(nouveauProjet()));

}

/*
void MainWindow::updateTree()
{
    model_tree->clear();
    afficher_projets(*model_tree);
}
*/
void MainWindow::nouveauProjet()
{
    DialogProjet* d = &DialogProjet::getInstance();
    d->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficher_projets(QStandardItemModel& m)
{

    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        QStandardItem* item = new QStandardItem((*it).getTitre());
        m.appendRow(item);
        afficher_taches(item, (*it));
    }
}

void MainWindow::afficher_taches(QStandardItem* i, Projet& p)
{
    for(Projet::Iterator it = p.begin(); it != p.end(); ++it)
    {
       (*it).afficher(i);
        std::cout << "ol" << std::endl;
    }
}

