#include "dialogprogevt.h"
#include "ui_dialogprogevt.h"
#include "agenda.h"
#include <iostream>

DialogProgEvt::DialogProgEvt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProgEvt)
{
    ui->setupUi(this);
    ui->un_jour->setChecked(true);


    adaptTimeDebut(QDate::currentDate());
    adaptTimeFin(QDate::currentDate());

    isRdv(false);
    adaptForm(true);

    connect(ui->un_jour, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->is_rdv, SIGNAL(toggled(bool)), this, SLOT(isRdv(bool)));
    connect(ui->date, SIGNAL(dateChanged(QDate)), this, SLOT(adaptTimeDebut(QDate)));
    connect(ui->date_fin, SIGNAL(dateChanged(QDate)), this, SLOT(adaptTimeFin(QDate)));
}

void DialogProgEvt::adaptTimeDebut(QDate d)
{
    //ajoute les contraintes sur la date de début et l'horaire de début
    ui->date->setMinimumDate(d);
    ui->date_fin->setMinimumDate(ui->date->date().addDays(1));
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
void DialogProgEvt::adaptTimeFin(QDate d)
{
    //ajoute les contraintes sur la date de fin et l'horaire de fin
    ui->horaire_fin->setMaximumTime(QTime(22,0));
    if(d == QDate::currentDate())
    {
        if(QTime::currentTime() < QTime(8,0))
            ui->horaire_fin->setMinimumTime(QTime(8,0));
        else
            ui->horaire_fin->setMinimumTime(QTime::currentTime());
    }
    else
    {
        ui->horaire->setMinimumTime(QTime(8,0));
    }
}

void DialogProgEvt::isRdv(bool etat)
{
    if(etat==true)
    {
        ui->lieu->show();
        ui->label_lieu->show();
        ui->personnes->show();
        ui->label_personnes->show();
    }
    else
    {
        ui->lieu->hide();
        ui->label_lieu->hide();
        ui->personnes->hide();
        ui->label_personnes->hide();
    }
}


void DialogProgEvt::adaptForm(bool etat)
{
    if(etat)
    {
        ui->date_fin->hide();
        ui->horaire_fin->hide();
        ui->label_date_fin->hide();
        ui->label_horaire_fin->hide();
        ui->duree->show();
        ui->label_duree->show();
        ui->is_rdv->show();
        ui->lieu->show();
        ui->label_lieu->show();
        ui->personnes->show();
        ui->label_personnes->show();
        isRdv(false);

    }
    else
    {
        ui->date_fin->show();
        ui->label_date_fin->show();
        ui->horaire_fin->show();
        ui->label_horaire_fin->show();
        ui->duree->hide();
        ui->label_duree->hide();
        ui->is_rdv->hide();
        ui->lieu->hide();
        ui->label_lieu->hide();
        ui->personnes->hide();
        ui->label_personnes->hide();
    }
}

/*
 * 0 : evt 1 jour
 * 1 : evt rdv
 * 2 : evt pls jour
*/

void DialogProgEvt::accept()
{
    try
    {
        if(ui->titre->text() == "" || ui->desc->toPlainText() == "")
        {
            throw CalendarException("Veuillez entrer un titre et une description");
        }
        Agenda* ag = &Agenda::getInstance();
        //ajoute le bon type d'évènement en fonction en fonction des informations entrées
        if(ui->un_jour->isChecked())
        {
            if(ui->is_rdv->isChecked())
            {
                ag->ajouterProgrammation(1,ui->date->date(),ui->titre->text(),ui->desc->toPlainText(),
                                         ui->horaire->time(),
                                         Duree(ui->duree->time().hour(), ui->duree->time().minute()),
                                         ui->lieu->text(), ui->personnes->toPlainText());
            }
            else
            {
                ag->ajouterProgrammation(0,ui->date->date(),ui->titre->text(),ui->desc->toPlainText(),
                                         ui->horaire->time(),
                                         Duree(ui->duree->time().hour(), ui->duree->time().minute()));
            }
        }
        else
        {
            ag->ajouterProgrammationPlsJour(ui->date->date(),ui->titre->text(),ui->desc->toPlainText(),
                                            ui->horaire->time(), ui->date_fin->date(), ui->horaire_fin->time());
        }
        close();
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(0, "Erreur", e.getInfo());

    }
}

DialogProgEvt::~DialogProgEvt()
{
    delete ui;
}
