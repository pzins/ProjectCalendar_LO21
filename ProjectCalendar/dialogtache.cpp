#include "dialogtache.h"
#include "ui_dialogtache.h"
#include "duree.h"
#include <iostream>

DialogTache* DialogTache::instance = 0;

DialogTache& DialogTache::getInstance(QWidget* parent)
{
    if(instance){
        instance->update();
        return *instance;
    }
    else
    {
        instance = new DialogTache(parent);
        instance->update();
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
    ajouterObservateur(pm);
    connect(ui->isComposite, SIGNAL(clicked(bool)), this, SLOT(updateDuree(bool)));
    connect(ui->projet, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateComposite(QString)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(valider()));
}

DialogTache::~DialogTache()
{
    delete ui;
}

void DialogTache::update()
{
    ui->projet->clear();
   for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
       ui->projet->addItem((*it).getTitre(), (*it).getId());
    }
    updateComposite(ui->projet->currentText());
}


void DialogTache::updateComposite(QString titre)
{
    ui->composite->clear();
    ui->composite->addItem("",-1);
    Projet* p = pm->getProjet(titre);
    if (p)
    {
        for(Projet::Iterator it = p->begin(); it != p->end(); ++it)
            (*it).afficherComposite(*ui->composite);
    }
}


void DialogTache::updateDuree(bool etat)
{

    if(etat)
        ui->duree->setEnabled(false);
    else ui->duree->setEnabled(true);
}

void DialogTache::valider()
{
    Projet* p = pm->getProjet(ui->projet->currentText());
    if(p)
    {
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
            TacheComposite* t = p->getTacheComposite(ui->composite->currentText());

            if(ui->isComposite->isChecked())
            {
                TacheComposite* tc = t->ajouterTacheComposite(ui->titre->text(), ui->descr->toPlainText(),
                                                 ui->dispo->date(), ui->eche->date());
                 p->getMapTacheComposite().insert(std::make_pair(ui->titre->text(),tc));

            }
            else
            {
                t->ajouterTacheUnitaire(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(),
                   ui->eche->date(), Duree(ui->duree->time().hour(), ui->duree->time().minute()));
            }
        }
        notifier();
    }
}
void DialogTache::ajouterObservateur(Observateur* o){obs.insert(o);}
void DialogTache::supprimerObservateur(Observateur* o){obs.erase(o);}
void DialogTache::notifier()
{
    for(std::set<Observateur*>::iterator it = obs.begin(); it != obs.end(); ++it)
    {
        (*it)->update();
    }
}
