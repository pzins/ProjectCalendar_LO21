#include "dialogprecedence.h"
#include "ui_dialogprecedence.h"

#include <QMessageBox>

DialogPrecedence* DialogPrecedence::instance = 0;


DialogPrecedence& DialogPrecedence::getInstance(QWidget* parent)
{
    if(instance)
    {
        instance->chargement();
        return *instance;
    }
    else
    {
        instance = new DialogPrecedence(parent);
        return *instance;
    }
}

void DialogPrecedence::libererInstance()
{
    delete instance;
    instance = 0;
}

DialogPrecedence::DialogPrecedence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrecedence)
{
    ui->setupUi(this);
    pm = &ProjetManager::getInstance();
    pre = &PrecedenceManager::getInstance();
    chargement();
    connect(ui->projet, SIGNAL(currentIndexChanged(QString)), this, SLOT(chargerTaches(QString)));
}

DialogPrecedence::~DialogPrecedence()
{
    delete ui;
}


void DialogPrecedence::accept()
{
    try
    {
        if(pm->getMapProjet().size() == 0)
            throw CalendarException("Aucun Projet, aucune tache");
        if(ui->anterieure->currentText() == ui->posterieure->currentText())
            throw CalendarException("Precedence impossible entre avec la elle même");
        Projet* p = pm->getProjet(ui->projet->currentText());
        Tache* ant = p->getTache(ui->anterieure->currentText());
        Tache* post = p->getTache(ui->posterieure->currentText());
        pre->ajouterPrecedence(*ant, *post, *p);
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }
    this->close();
}

void DialogPrecedence::chargerProjets()
{
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        ui->projet->addItem((*it).getTitre());
    }
}

void DialogPrecedence::chargerTaches(QString titre)
{
    ui->anterieure->clear();
    ui->posterieure->clear();
    Projet* p = pm->getProjet(titre);
    for(Projet::Iterator it = p->begin(); it != p->end(); ++it)
    {
        ui->anterieure->addItem((*it).getTitre());
        ui->posterieure->addItem((*it).getTitre());
    }
}

void DialogPrecedence::chargement()
{
    if(pm->getMapProjet().size() > 0)
    {
        chargerProjets();
        chargerTaches(ui->projet->currentText());
    }
}
