#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "precedenceitem.h"
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
/*
    pm->ajouterProjet("ol","...",QDate(2000,3,5),QDate(2003,2,5));
    pm->ajouterProjet("lyon","...", QDate(2000,3,5),QDate(2003,2,5));
    Projet* pro1 = (pm->getProjet("ol"));

    pro1->ajouterTache(QChar('U'),"tache1","...",QDate(2000,3,5), QDate(2000,20,2), 5);
    pro1->ajouterTache(QChar('C'),"tache2","...",QDate(2000,3,5), QDate(2003,2,5));


    TacheComposite* c = pro1->getTacheComposite("tache2");
    c->ajouter("tache3","...",QDate(2000,3,5), QDate(2003,1,5), );

*/

    ui->treeView->setModel(&pm->getModel());
    ag = &Agenda::getInstance();
    pre = &PrecedenceManager::getInstance();
    pre->ajouterObservateur(this);
    ui->treeView->setAnimated(true);
//    pm->update();


    /*
    QStandardItem *parentItem = model.invisibleRootItem();

    for (int i = 0; i < 4; ++i) {
        Projet *object = new Projet("oko",QDate(2000,5,2), QDate(2001,2,3));
        QVariant variant;
        variant.setValue(object);
        QStandardItem *item = new QStandardItem;
        item->setData(variant.toString());
        parentItem->appendRow(item);
        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
        QStandardItem *item = new TacheUnitaire("ol","lyon",QDate(2000,2,2), QDate(2003,3,3),Duree(3,3));
        item->setText("hfghjol");
        parentItem->appendRow(item);
        parentItem = item;
    }
    ui->treeView->setModel(&model);
*/
    connect(ui->tacheunitaire, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->tachecomposite, SIGNAL(toggled(bool)), this, SLOT(adaptForm2(bool)));
    connect(ui->projet, SIGNAL(toggled(bool)), this, SLOT(adaptForm2(bool)));

    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(ui->precedence, SIGNAL(clicked()), this, SLOT(ajouterPrecedence()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(sauvegarder()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(charger()));
    connect(ui->expand, SIGNAL(clicked()), this, SLOT(expand()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(supprimerItem()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(afficherInfo(QModelIndex)));
    connect(ui->supprimer_precedence, SIGNAL(clicked()), this, SLOT(supprimer_precedence()));
}

void MainWindow::ajouterPrecedence()
{
    DialogPrecedence* d = &DialogPrecedence::getInstance();
    d->show();

}

void MainWindow::expand()
{
    ui->treeView->expandAll();
}

void MainWindow::supprimer_precedence()
{
    PrecedenceItem* element = dynamic_cast<PrecedenceItem*>(ui->precedence_list->currentItem());
    pre->retirerPrecedence(*element->getPrecedence());
    delete element->getPrecedence();
    ui->precedence_list->removeItemWidget(ui->precedence_list->currentItem());
}


void MainWindow::afficherInfo(QModelIndex idx)
{

    ui->info->setHtml(pm->getInfo(idx));

}

void MainWindow::supprimerItem()
{
    QModelIndexList sel = ui->treeView->selectionModel()->selectedRows();
    for(int i = 0; i < sel.size(); ++i)
        pm->supprimerItem(sel[i]);


    std::cout << "=========================================" << std::endl;
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        std::cout << "\n" << (*it).getTitre().toStdString() << std::endl;
        for(Projet::Iterator i = (*it).begin(); i != (*it).end(); ++i)
        {
            std::cout <<"---" << (*i).getTitre().toStdString() << std::endl;
        }
    }
    std::cout << "=========================================" << std::endl;
}


void MainWindow::adaptForm(bool etat)
{
    if(etat == true)
    {
        ui->isPreemptive->show();
        ui->duree->show();
        ui->label_duree->show();
    }
    else
    {
        ui->duree->hide();
        ui->label_duree->hide();
        ui->isPreemptive->hide();
    }
}
void MainWindow::adaptForm2(bool etat)
{
    if(etat == false)
    {
        ui->isPreemptive->show();
        ui->duree->show();
        ui->label_duree->show();
    }
    else
    {
        ui->duree->hide();
        ui->label_duree->hide();
        ui->isPreemptive->hide();
    }
}



void MainWindow::ajouter()
{
    QModelIndexList sel = ui->treeView->selectionModel()->selectedRows();
    QModelIndex idx, idx_parent;
    if(sel.size() == 1)
    {
        idx = sel.at(0);
        idx_parent = idx;
        while(idx_parent.parent().data().toString() != "") idx_parent = idx_parent.parent();
    }
    if(ui->projet->isChecked() == true)
    {
        try
        {
            pm->verification(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date());
            pm->ajoutItemModel(ui->titre->text(), pm->getModel().invisibleRootItem()->index());
            pm->ajouterProjet(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date());
        }
        catch(CalendarException e)
        {
            QMessageBox::critical(this, "Erreur", e.getInfo());
        }

    }
    else if (sel.size() == 1 && (ui->tacheunitaire->isChecked() == true || ui->tachecomposite->isChecked() == true))
    {
        Projet* p;
        bool ajout_a_projet;
        if(idx.parent().data().toString() == "")
        {
            p = pm->getProjet(idx.data().toString());
            ajout_a_projet = true;
        }
        else
        {
            p = pm->getProjet(idx_parent.data().toString());
            ajout_a_projet = false;
        }

        if(p && (ajout_a_projet || p->getTache(idx.data().toString())->isComposite()))
        {
            try
            {
                p->verification(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date(),
                                idx.data().toString());
                pm->ajoutItemModel(ui->titre->text(), idx);
                if(ui->tacheunitaire->isChecked())
                {
                    p->ajouterTache(QChar('U'), ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date(),
                                    Duree(ui->duree->time().hour(), ui->duree->time().minute()), ui->isPreemptive->isChecked());
                }
                else
                {
                    p->ajouterTache(QChar('C'), ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date(),
                                    Duree(ui->duree->time().hour(), ui->duree->time().minute()), ui->isPreemptive->isChecked());
                }
            }
            catch(CalendarException e)
            {
                QMessageBox::critical(this, "Erreur", e.getInfo());
            }
        }
    }
}


void MainWindow::sauvegarder()
{
    pm->save("projets.xml");
    pm->saveModel("model.xml");
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        (*it).save((*it).getTitre() + QString(".xml"));
    }

}

void MainWindow::charger()
{
   // QString chemin = QFileDialog::getOpenFileName();
    //supprimerAllItem();
    pm->load("projets.xml");
    pm->loadModel("model.xml");
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        (*it).load((*it).getTitre() + QString(".xml"));
    }

}

void MainWindow::update()
{
    ui->precedence_list->clear();
    for(PrecedenceManager::Iterator it = pre->begin(); it != pre->end(); ++it)
    {
        ui->precedence_list->addItem(new PrecedenceItem((*it).toString(),&(*it)));
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
