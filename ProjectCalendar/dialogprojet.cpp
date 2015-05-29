#include "dialogprojet.h"
#include "ui_dialogprojet.h"

#include <iostream>
#include <QMessageBox>

DialogProjet* DialogProjet::instance = 0;

DialogProjet& DialogProjet::getInstance(QWidget* parent)
{
    if(instance) return *instance;
    else
    {
        instance = new DialogProjet(parent);
        return *instance;
    }

}

void DialogProjet::libererInstance()
{
    delete instance;
    instance = 0;
}


DialogProjet::DialogProjet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProjet)
{
    ui->setupUi(this);
    pm = &ProjetManager::getInstance();
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(valider()));

}

DialogProjet::~DialogProjet()
{
    delete ui;
}


void DialogProjet::valider()
{
    try
    {
        pm->ajouterProjet(ui->lineEdit->text(), ui->dateEdit->date(), ui->dateEdit_2->date());
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }
}
