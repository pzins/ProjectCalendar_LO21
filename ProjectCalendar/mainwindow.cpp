#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>


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
/*
    pm->ajouterProjet("ol",QDate(2000,5,6),QDate(2003,2,5));
    pm->ajouterProjet("lyon",QDate(2000,5,6),QDate(2003,2,5));
    Projet* pro1 = &(pm->getProjet("ol"));

    pro1->ajouterTacheUnitaire("tache1","...",QDate(2012,3,5), QDate(2012,20,6), 5);
    pro1->ajouterTacheComposite("tache2","...",QDate(2012,3,5), QDate(2012,20,6));


    TacheComposite* c = dynamic_cast<TacheComposite*>(&pro1->getTache("tache2"));
    c->ajouterTacheUnitaire("tache3","...",QDate(2012,3,5), QDate(2012,20,6), Duree(5,2));
*/



    ag = &Agenda::getInstance();

    pm->remplirModel();
    ui->treeView->setModel(&pm->getModel());
    connect(ui->nouveau_projet, SIGNAL(clicked()),this,SLOT(nouveauProjet()));
    connect(ui->ajouter_tache, SIGNAL(clicked()),this,SLOT(ajouterTache()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(sauvegarder()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(charger()));
}

void MainWindow::nouveauProjet()
{
    DialogProjet* d = &DialogProjet::getInstance();
    d->show();
}

void MainWindow::ajouterTache()
{
    DialogTache* d = &DialogTache::getInstance();
    d->show();
}

void MainWindow::sauvegarder()
{
    pm->save("projets.xml");
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
        (*it).save((*it).getTitre() + QString(".xml"));
}

void MainWindow::charger()
{
    QString chemin = QFileDialog::getOpenFileName();
    pm->load(chemin);
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        (*it).load((*it).getTitre() + QString(".xml"));
    }
    pm->remplirModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}


