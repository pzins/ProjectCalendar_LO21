#include "dialogprogevt.h"
#include "ui_dialogprogevt.h"
#include "agenda.h"
#include <iostream>

DialogProgEvt* DialogProgEvt::instance = 0;


DialogProgEvt& DialogProgEvt::getInstance(QWidget* parent)
{
    if(instance)
    {
        return *instance;
    }
    else
    {
        instance = new DialogProgEvt(parent);
        return *instance;
    }
}

void DialogProgEvt::libererInstance()
{
    delete instance;
    instance = 0;
}


DialogProgEvt::DialogProgEvt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProgEvt)
{
    ui->setupUi(this);
    ui->un_jour->setChecked(true);
    isReunion(false);
    adaptForm(true);
    connect(ui->un_jour, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->is_reunion, SIGNAL(toggled(bool)), this, SLOT(isReunion(bool)));
}



void DialogProgEvt::isReunion(bool etat)
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
        ui->is_reunion->show();
        ui->lieu->show();
        ui->label_lieu->show();
        ui->personnes->show();
        ui->label_personnes->show();
        isReunion(false);

    }
    else
    {
        ui->date_fin->show();
        ui->label_date_fin->show();
        ui->horaire_fin->show();
        ui->label_horaire_fin->show();
        ui->duree->hide();
        ui->label_duree->hide();
        ui->is_reunion->hide();
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
    Agenda* ag = &Agenda::getInstance();
    if(ui->un_jour->isChecked())
    {
        if(ui->is_reunion->isChecked())
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
        ag->ajouterProgrammationPlsJour(ui->date->date(),ui->titre->text(),ui->desc->toPlainText(), ui->horaire->time(),
                                        ui->date_fin->date(), ui->horaire_fin->time());
    }
    close();
}

DialogProgEvt::~DialogProgEvt()
{
    delete ui;
}
