#include "dialogprogtache.h"
#include "ui_dialogprogtache.h"
#include "agenda.h"
#include "dialogprogpartie.h"


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
    DialogProgPartie* d = new DialogProgPartie(ui->nb->value(), vec_titre, vec_date, vec_debut, vec_duree, this);
    d->exec();
}

void DialogProgTache::adaptForm(bool etat)
{
    if(etat)
    {
        ui->nb->show();
        ui->label_nb->show();
        ui->ajouter->show();
        ui->date->hide();
        ui->horaire->hide();
        ui->label_horaire->hide();
        ui->label_date->hide();
    }
    else
    {
        ui->nb->hide();
        ui->label_nb->hide();
        ui->ajouter->hide();
        ui->date->show();
        ui->horaire->show();
        ui->label_horaire->show();
        ui->label_date->show();
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
            ag->ajouterProgrammationPartieTache(vec_date, vec_titre, vec_debut, vec_duree, tache, projet->getTitre());
        }
        else
        {
            ag->ajouterProgrammation(2, ui->date->date(), tache->getTitre(), tache->getDescription(),ui->horaire->time(),
                                     tache->getDuree(),"", "", tache, projet->getTitre());
        }
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
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
        if(i < vec_duree.size() -1)
        {
            QDate d = vec_date.at(i);
            QDate dd = vec_date.at(i+1);
            QTime deb = vec_debut.at(i);
            QTime debdeb = vec_debut.at(i+1);
            if((d > dd) || (d==dd && deb > debdeb))
                throw CalendarException("Ordre des parties incohérentes");
            if(d==dd && deb == debdeb)
                throw CalendarException("Les parties ne peuvent pas avoir la même programmation");
            QTime fin = deb.addSecs(vec_duree.at(i).getDureeEnMinutes()*60);
            if(d==dd && fin > debdeb)
                throw CalendarException("Les parties se chevauchent");
        }
    }
    Duree d(min);
    if(!(tache->getDuree() == d)) throw CalendarException("Somme des durées des parties non cohérentes");
    for(int i = 0; i < vec_debut.size(); ++i)
    {
        if(vec_date.at(i) < tache->getDispo() || vec_date.at(i) > tache->getEcheance())
            throw CalendarException("Parties non conforme avec la disponibilité et échéance de la tache");

    }
}
