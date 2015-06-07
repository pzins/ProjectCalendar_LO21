#include "dialogprogtache.h"
#include "ui_dialogprogtache.h"
#include "agenda.h"
#include "precedence.h"
#include "programmationtacheunitaire.h"
#include "programmation.h"
#include "dialogprogpartie.h"

DialogProgTache* DialogProgTache::instance = 0;


DialogProgTache& DialogProgTache::getInstance(TacheUnitaire* tache, Projet* projet, QWidget* parent)
{
    if(instance)
    {
        instance->setTache(tache);
        instance->setProjet(projet);
        instance->ui->parties->setChecked(false);
        if(!tache->isPreemptive())
        {
            instance->ui->parties->setEnabled(false);
        }
        else
        {
            instance->ui->parties->setEnabled(true);

        }
        instance->ui->nb->hide();
        instance->ui->label_nb->hide();
        instance->ui->date->setDate(QDate::currentDate());
        return *instance;
    }
    else
    {
        instance = new DialogProgTache(tache, projet, parent);
        return *instance;
    }
}

void DialogProgTache::libererInstance()
{
    delete instance;
    instance = 0;
}

DialogProgTache::DialogProgTache(TacheUnitaire* tache_, Projet* projet_, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogProgTache),
    projet(projet_), tache(tache_)

{
    ui->setupUi(this);
    if(!tache_->isPreemptive())
    {
        ui->parties->setEnabled(false);
    }
    ui->nb->hide();
    ui->label_nb->hide();
    ui->ajouter->hide();
    ui->date->setDate(QDate::currentDate());
    connect(ui->parties, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajouterParties()));
}

DialogProgTache::~DialogProgTache()
{
    delete ui;
}

void DialogProgTache::ajouterParties()
{
    DialogProgPartie* d = &DialogProgPartie::getInstance(ui->nb->value(), vec_titre, vec_date, vec_debut, vec_duree, this);
    d->show();
}

void DialogProgTache::adaptForm(bool etat)
{
    if(etat)
    {
        ui->nb->show();
        ui->label_nb->show();
        ui->ajouter->show();
    }
}


void DialogProgTache::accept()
{
    Agenda* ag = &Agenda::getInstance();
    try
    {
        verification();
        if(ui->parties->isChecked())
        {
            verificationParties();
            for(int i = 0; i < vec_titre.size(); ++i)
            {
                ag->ajouterProgrammationPartieTache(vec_date, vec_titre, vec_debut, vec_duree, tache);
            }
        }
        else
        {
            ag->ajouterProgrammation(2, ui->date->date(), tache->getTitre(), tache->getDescription(),ui->horaire->time(),
                                     tache->getDuree(),"", "", tache );

        }
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }

    close();
}

void DialogProgTache::verification()
{
    if(tache->getDispo() > ui->date->date()) throw CalendarException("Tache pas encore disponible");
    if(tache->getEcheance() < ui->date->date()) throw CalendarException("Echéance dépassée");
    Agenda* ag = &Agenda::getInstance();
    std::vector<Precedence*> vec = PrecedenceManager::getInstance().findPrecedence(projet, tache);
    for(std::vector<Precedence*>::iterator ite = vec.begin(); ite != vec.end(); ++ite)
    {
        //boucle sur ttes les précédence dt la tache succ ou pred est celle que l'on prog
        if(tache->getTitre() == (*ite)->getSucc().getTitre() || tache->getTitre() == (*ite)->getPred().getTitre())
        {
            for(Agenda::Iterator it = ag->begin(); it != ag->end(); ++it)//boucle sur ttes les taches déjà prog
            {
                //verif que c'est bien une prog de tache
                if((*it).isTache())
                {
                    if(tache->getTitre() == (*ite)->getSucc().getTitre())
                    {
                        //nouvelle prog est succ => une autre doit être finie avant
                        //nouvelle : tache
                        //anterieure : ptu
                        //conv en prog de tache uni
                        ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(&(*it));
                        if(ptu->getDate() > ui->date->date() ||
                          (ptu->getDate() == ui->date->date() && ptu->getDebut() > ui->horaire->time()))
                        {
                            throw CalendarException("Incohérence avec les contraintes de Précédences");
                        }
                    }
                    else
                    {
                        //nouvelle prog est pred => doit être finie avant autre
                        //nouvelle : tache
                        //anterieure : ptu
                        //conv en prog de tache uni
                        ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(&(*it));
                        if(ptu->getDate() < ui->date->date() ||
                          (ptu->getDate() == ui->date->date() && ptu->getDebut() < ui->horaire->time()))
                        {
                            throw CalendarException("Incohérence avec les contraintes de Précédences");
                        }
                    }
                }
            }
        }
    }
}

void DialogProgTache::verificationParties()
{
    int min = 0;
    for(int i = 0; i < vec_duree.size(); ++i)
    {
        min += vec_duree.at(i).getHeure()*60;
        min += vec_duree.at(i).getMinute();
    }
    Duree d(min);
    if(!(tache->getDuree() == d)) throw CalendarException("Somme des durées des parties non cohérentes");
    for(int i = 0; i < vec_debut.size(); ++i)
    {
        if(vec_date.at(i) < tache->getDispo() || vec_date.at(i) > tache->getEcheance())
            throw CalendarException("Parties non conforme avec la disponibilité et échéance de la tache");

    }
}
