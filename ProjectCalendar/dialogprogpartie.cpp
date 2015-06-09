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
}

DialogProgPartie::~DialogProgPartie()
{
    delete ui;
}



void DialogProgPartie::initialisation(int nb)
{
    //génération du bon nombre de formulaire (date, horaire et durée)
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
        p->debut->setMaximumTime(QTime(22,0));
        p->debut->setMinimumTime(QTime(8,0));
        p->duree = new QTimeEdit(this);
        p->duree->setMaximumTime(QTime(12,0));
        vec_parties.push_back(p);
    }
    //affichage des éléments
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
    //ajout des programmations de partie dans les vecteurs
    for(int i = 0; i < vec_parties.size(); ++i)
    {
        vec_titre.push_back(vec_parties.at(i)->titre->text());
        vec_date.push_back(vec_parties.at(i)->date->date());
        vec_debut.push_back(vec_parties.at(i)->debut->time());
        vec_duree.push_back(Duree(vec_parties.at(i)->duree->time().hour(), vec_parties.at(i)->duree->time().minute()));
    }
    close();
}
