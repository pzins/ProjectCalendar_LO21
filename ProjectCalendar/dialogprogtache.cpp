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
    adaptTime(QDate::currentDate());
    connect(ui->parties, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->date, SIGNAL(dateChanged(QDate)), this, SLOT(adaptTime(QDate)));
    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajouterParties()));
}

void DialogProgTache::adaptTime(QDate d)
{
    //ajoute les contraintes sur la date et l'horaire de début
    ui->date->setMinimumDate(d);
    ui->horaire->setMaximumTime(QTime(22,0));
    if(d == QDate::currentDate())
    {
        if(QTime::currentTime() < QTime(8,0))
            ui->horaire->setMinimumTime(QTime(8,0));
        else
            ui->horaire->setMinimumTime(QTime::currentTime());
    }
    else
    {
        ui->horaire->setMinimumTime(QTime(8,0));
    }
}

DialogProgTache::~DialogProgTache()
{
    delete ui;
}

void DialogProgTache::ajouterParties()
{
    //ouvre une nouvelle fenêtre de dialogue si on veut programmer des parties
    //on passe des vecteurs par références dans lesquelles seront ajouté les informations des parties
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
        //ajout des parties de la tache dans l'agenda
        if(ui->parties->isChecked())
        {
            verificationParties();
            ag->ajouterProgrammationPartieTache(vec_date, vec_titre, vec_debut, vec_duree, tache, projet);
        }
        //sinon ajout de la tache unitaire dans l'agenda
        else
        {
            ag->ajouterProgrammation(2, ui->date->date(), tache->getTitre(), tache->getDescription(),ui->horaire->time(),
                                     tache->getDuree(),"", "", tache, projet);
        }
        close();
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }

}

void DialogProgTache::verification()
{
    if(tache->getDispo() > ui->date->date()) throw CalendarException("Tache pas encore disponible");
    if(tache->getEcheance() < ui->date->date()) throw CalendarException("Echéance dépassée");
    Agenda* ag = &Agenda::getInstance();
    //boucles sur les precedences pour vérifier la cohérence
    std::vector<Precedence*> vec = PrecedenceManager::getInstance().findPrecedence(projet, tache);
    for(std::vector<Precedence*>::iterator ite = vec.begin(); ite != vec.end(); ++ite)
    {
        //boucle sur ttes les précédences dt la tache succ ou pred est celle que l'on programme
        if(tache->getTitre() == (*ite)->getSucc().getTitre() || tache->getTitre() == (*ite)->getPred().getTitre())
        {
            for(Agenda::Iterator it = ag->begin(); it != ag->end(); ++it)//boucle sur ttes les taches déjà programmées
            {
                //verif que c'est bien une prog de tache
                if((*it).isTache())
                {
                    //si la tache est la tache antérieure de la précédence
                    if(tache->getTitre() == (*ite)->getSucc().getTitre())
                    {
                        ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(&(*it));
                        if(ptu->getDate() > ui->date->date() ||
                          (ptu->getDate() == ui->date->date() && ptu->getDebut() > ui->horaire->time()))
                        {
                            throw CalendarException("Incohérence avec les contraintes de Précédences");
                        }
                    }
                    //sinon la tache est la tache postérieure de la précédence
                    else
                    {
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
    //on parcours toutes les parties
    for(int i = 0; i < vec_duree.size(); ++i)
    {
        //on faite la somme des durée pour vérifier que la somme == durée de la tache
        min += vec_duree.at(i).getHeure()*60;
        min += vec_duree.at(i).getMinute();
        if(i < vec_duree.size() -1)
        {
            QDate d = vec_date.at(i);
            QDate dd = vec_date.at(i+1);
            QTime deb = vec_debut.at(i);
            QTime debdeb = vec_debut.at(i+1);
            //on vérifie l'ordre des parties
            if((d > dd) || (d==dd && deb > debdeb))
                throw CalendarException("Ordre des parties incohérentes");
            //date et horaire différents
            if(d==dd && deb == debdeb)
                throw CalendarException("Les parties ne peuvent pas avoir la même programmation");
            QTime fin = deb.addSecs(vec_duree.at(i).getDureeEnMinutes()*60);
            //chevauchements
            if(d==dd && fin > debdeb)
                throw CalendarException("Les parties se chevauchent");
        }
        //vérifie la cohérence avec disponibilité et échéance
        if(vec_date.at(i) < tache->getDispo() || vec_date.at(i) > tache->getEcheance())
            throw CalendarException("Parties non conforme avec la disponibilité et échéance de la tache");
    }
    Duree d(min);
    if(!(tache->getDuree() == d)) throw CalendarException("Somme des durées des parties non cohérentes");
}
