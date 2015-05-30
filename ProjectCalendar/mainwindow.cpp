#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

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

    pm->ajouterProjet("ol",QDate(2000,3,5),QDate(2003,2,5));
    pm->ajouterProjet("lyon",QDate(2000,3,5),QDate(2003,2,5));
    Projet* pro1 = (pm->getProjet("ol"));

    pro1->ajouterTacheUnitaire("tache1","...",QDate(2000,3,5), QDate(2000,20,2), 5);
    pro1->ajouterTacheComposite("tache2","...",QDate(2000,3,5), QDate(2003,2,5));


    TacheComposite* c = pro1->getTacheComposite("tache2");
    c->ajouterTacheUnitaire("tache3","...",QDate(2000,3,5), QDate(2003,1,5), Duree(5,2));




    ag = &Agenda::getInstance();
    ui->treeView->setAnimated(true);
    pm->update();
    ui->treeView->setModel(&pm->getModel());
    ui->treeView->setSelectionMode(QTreeView::ExtendedSelection);
    ui->treeView->setSelectionBehavior(QTreeView::SelectRows);


    connect(ui->nouveau_projet, SIGNAL(clicked()),this,SLOT(nouveauProjet()));
    connect(ui->ajouter_tache, SIGNAL(clicked()),this,SLOT(ajouterTache()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(sauvegarder()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(charger()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
}

void MainWindow::nouveauProjet()
{
    DialogProjet* d = &DialogProjet::getInstance();
    d->show();
}

void MainWindow::ajouterTache()
{
    try
    {
        if(pm->getMapProjet().size() == 0) throw CalendarException("Aucun Projet");
        DialogTache* d = &DialogTache::getInstance();
        d->show();
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }
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
    pm->update();
}

void MainWindow::supprimer()
{
        QModelIndexList sel = ui->treeView->selectionModel()->selectedRows();
        QString selection;
        for(int i = 0; i < sel.size(); ++i)
        {
            std::cout << sel.at(i).data().toString().toStdString() << std::endl;
            selection = sel.at(i).data().toString();
        }
        for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
        {
            std::cout << "ol" << std::endl;
           (*it).suppressionTache(selection, (*it).getMapTache());
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


