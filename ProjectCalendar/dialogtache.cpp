#include "dialogtache.h"
#include "ui_dialogtache.h"
#include "duree.h"
#include <iostream>

DialogTache* DialogTache::instance = 0;

DialogTache& DialogTache::getInstance(QWidget* parent)
{
    if(instance) return *instance;
    else
    {
        instance = new DialogTache(parent);
        return *instance;
    }
}

void DialogTache::libererInstance()
{
    delete instance;
    instance = 0;
}

DialogTache::DialogTache(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTache)
{
    ui->setupUi(this);
    pm = &ProjetManager::getInstance();
    afficherProjets();
    connect(ui->isComposite, SIGNAL(clicked(bool)), this, SLOT(autoriserDuree(bool)));
    connect(ui->projet, SIGNAL(currentIndexChanged(QString)), this, SLOT(afficherComposite(QString)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(valider()));
}

DialogTache::~DialogTache()
{
    delete ui;
}

void DialogTache::afficherProjets()
{
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
        ui->projet->addItem((*it).getTitre(), (*it).getId());
}
void DialogTache::afficherComposite(QString titre)
{
    ui->composite->clear();
    ui->composite->addItem("",-1);
    Projet* p = &pm->getProjet(titre);
    for(Projet::Iterator it = p->begin(); it != p->end(); ++it)
        (*it).afficherComposite(*ui->composite);
}

void DialogTache::autoriserDuree(bool etat)
{

    if(etat)
        ui->duree->setEnabled(false);
    else ui->duree->setEnabled(true);
}

void DialogTache::valider()
{
    Projet* p = &pm->getProjet(ui->projet->currentText());
    if(ui->composite->currentData() == -1)
    {
        if(ui->isComposite->isChecked())
        {
            p->ajouterTacheComposite(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date());
        }
        else
        {
            p->ajouterTacheUnitaire(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(),
                                    ui->eche->date(), Duree(ui->duree->time().hour(), ui->duree->time().minute()));
        }
    }
    else
    {
        TacheComposite* t = dynamic_cast<TacheComposite*>(&p->getTache(ui->composite->currentText()));
        if(ui->isComposite->isChecked())
        {
            t->ajouterTacheComposite(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date());
        }
        else
        {
            t->ajouterTacheUnitaire(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(),
                                    ui->eche->date(), Duree(ui->duree->time().hour(), ui->duree->time().minute()));
        }
    }
    pm->remplirModel();
}
