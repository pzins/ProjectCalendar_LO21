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
    ui->date->setMinimumDate(QDate::currentDate());
    ui->date_fin->setMinimumDate(QDate::currentDate());
    ui->horaire->setMinimumTime(QTime::currentTime());
    ui->horaire_fin->setMinimumTime(QTime::currentTime());

    isRdv(false);
    adaptForm(true);
    connect(ui->un_jour, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->is_rdv, SIGNAL(toggled(bool)), this, SLOT(isReunion(bool)));
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
        if(ui->un_jour->isChecked())
        {
            if(ui->is_rdv->isChecked())
            {
                ag->ajouterProgrammation(1,ui->date->date(),ui->titre->text(),ui->desc->toPlainText(), ui->horaire->time(),
                                     Duree(ui->duree->time().hour(), ui->duree->time().minute()),ui->lieu->text(),
                                         ui->personnes->toPlainText());
            }
            else
            {
                ag->ajouterProgrammation(0,ui->date->date(),ui->titre->text(),ui->desc->toPlainText(), ui->horaire->time(),
                                     Duree(ui->duree->time().hour(), ui->duree->time().minute()));
            }
        }
        else
        {
            if(QDateTime(ui->date->date(), ui->horaire->time()) >= QDateTime(ui->date_fin->date(), ui->horaire_fin->time()))
                throw CalendarException("Date et horaire de début et de fin incohérents");
            ag->ajouterProgrammationPlsJour(ui->date->date(),ui->titre->text(),ui->desc->toPlainText(), ui->horaire->time(),
                                            ui->date_fin->date(), ui->horaire_fin->time());
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
