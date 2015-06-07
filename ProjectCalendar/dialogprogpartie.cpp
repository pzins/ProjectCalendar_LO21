#include "dialogprogpartie.h"
#include "ui_dialogprogpartie.h"
#include <iostream>


DialogProgPartie::DialogProgPartie(int nb, std::vector<QString>& vec_titre_, std::vector<QDate> &vec_date_,
                                   std::vector<QTime> &vec_debut_, std::vector<Duree>& vec_duree_,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProgPartie),
    vec_date(vec_date_),vec_debut(vec_debut_), vec_titre(vec_titre_), vec_duree(vec_duree_)
{
    ui->setupUi(this);
    initialisation(nb);
    affichage();
}

DialogProgPartie::~DialogProgPartie()
{
    delete ui;
}



void DialogProgPartie::initialisation(int nb)
{
    while(!ui->verticalLayout->isEmpty()) {
        QWidget *w = ui->verticalLayout->takeAt(0)->widget();
        delete w;
    }
    vec_parties.clear();

    for(int i = 0; i < nb; ++i)
    {
        Partie* p = new Partie();
        QString tmp = "Partie ";
        tmp += QString::number(1+i);
        p->label = new QLabel(tmp, this);
        p->titre = new QLineEdit(this);
        p->date = new QDateEdit(this);
        p->date->setCalendarPopup(true);
        p->date->setDate(QDate::currentDate());
        p->debut = new QTimeEdit(this);
        p->duree = new QTimeEdit(this);
        vec_parties.push_back(p);
    }
}

void DialogProgPartie::affichage()
{
    for(int i = 0; i < vec_parties.size(); ++i)
    {
        ui->verticalLayout->addWidget(vec_parties.at(i)->label);
        ui->verticalLayout->addWidget(vec_parties.at(i)->titre);
        ui->verticalLayout->addWidget(vec_parties.at(i)->date);
        ui->verticalLayout->addWidget(vec_parties.at(i)->debut);
        ui->verticalLayout->addWidget(vec_parties.at(i)->duree);
        vec_parties.at(i)->label->show();
        vec_parties.at(i)->titre->show();
        vec_parties.at(i)->date->show();
        vec_parties.at(i)->debut->show();
        vec_parties.at(i)->duree->show();
    }
}

void DialogProgPartie::accept()
{
    for(int i = 0; i < vec_parties.size(); ++i)
    {
        vec_titre.push_back(vec_parties.at(i)->titre->text());
        vec_date.push_back(vec_parties.at(i)->date->date());
        vec_debut.push_back(vec_parties.at(i)->debut->time());
        vec_duree.push_back(Duree(vec_parties.at(i)->duree->time().hour(), vec_parties.at(i)->duree->time().minute()));
    }
    close();
}
