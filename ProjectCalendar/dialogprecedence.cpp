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

        std::vector<QString> vec;
        if(ant->isComposite())
        {
            vec = ProjetManager::getInstance().getTacheFilles(ant->getTitre(), p->getTitre());
            for(std::vector<QString>::iterator it = vec.begin()+1; it != vec.end(); ++it)
            {
                if(*it == post->getTitre())
                {
                    throw CalendarException("Précédence impossible entre tache mère et tache fille");
                }
                Tache* ante = p->getTache(*it);
                pre->ajouterPrecedence(*ante,*post, *p);
            }
        }
        else if(post->isComposite())
        {
            vec = ProjetManager::getInstance().getTacheFilles(post->getTitre(), p->getTitre());
            for(std::vector<QString>::iterator it = vec.begin()+1; it != vec.end(); ++it)
            {
                if(*it == ant->getTitre())
                {
                    throw CalendarException("Précédence impossible entre tache mère et tache fille");
                }
                Tache* poste = p->getTache(*it);
                pre->ajouterPrecedence(*ant,*poste, *p);
            }
        }
        pre->ajouterPrecedence(*ant, *post, *p);
        this->close();
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }
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
    if(ui->projet->currentText() != "")
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
}

void DialogPrecedence::chargement()
{
    if(pm->getMapProjet().size() > 0)
    {
        ui->anterieure->clear();
        ui->posterieure->clear();
        ui->projet->clear();
        chargerProjets();
        chargerTaches(ui->projet->currentText());
    }
}
