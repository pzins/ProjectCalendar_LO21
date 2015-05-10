#include "tacheEditeur.h"
#include "tachemanager.h"

TacheEditeur::TacheEditeur(Tache& ta, QWidget* parent):
    t(ta), QWidget(parent)
{
    this->vertical = new QVBoxLayout(this);

    couche1 = new QHBoxLayout;
    id = new QLabel("identificateur", this);
    idLineEdit = new QLineEdit(this);
    preemtive = new QCheckBox(this);
    couche1->addWidget(id);
    couche1->addWidget(idLineEdit);
    couche1->addWidget(preemtive);


    //deuxieme couche
    couche2 = new QHBoxLayout;
    titre = new QLabel("titre", this);
    titreLineEdit = new QLineEdit(this);
    couche2->addWidget(titre);
    couche2->addWidget(titreLineEdit);


    //troisieme couche

    couche3 = new QHBoxLayout;
    dispo = new QLabel("disponibilité", this);
    echeance= new QLabel("echeance", this);
    duree= new QLabel("duree", this);
    dateDispo = new QDateEdit(this);
    dateEcheance= new QDateEdit(this);
    dureeH = new QSpinBox(this);
    dureeM = new QSpinBox(this);
    couche3->addWidget(dispo);
    couche3->addWidget(echeance);
    couche3->addWidget(duree);
    couche3->addWidget(dateDispo);
    couche3->addWidget(dateEcheance);
    couche3->addWidget(dureeH);
    couche3->addWidget(dureeM);


    //quatrieme couche
    couche4 = new QHBoxLayout;
    annuler = new QPushButton("Annuler", this);
    sauver= new QPushButton("Sauver", this);
    couche4->addWidget(annuler);
    couche4->addWidget(sauver);


    vertical->addItem(couche1);
    vertical->addItem(couche2);
    vertical->addItem(couche3);
    vertical->addItem(couche4);


    idLineEdit->setText(t.getId());
    titreLineEdit->setText(t.getTitre());
    dateDispo->setDate(t.getDateDisponibilite());
    dateEcheance->setDate(t.getDateEcheance());
    dureeH->setValue(t.getDuree().getHeure());
    dureeM->setValue(t.getDuree().getMinute());

    sauver->setEnabled(false);

    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(sauverTache()));
    QObject::connect(preemtive, SIGNAL(stateChanged(int)), sauver, SLOT(activerButton()));
    QObject::connect(idLineEdit, SIGNAL(textChanged(QString)), sauver, SLOT(activerButton()));
    QObject::connect(titreLineEdit, SIGNAL(textChanged(QString)), sauver, SLOT(activerButton()));
    QObject::connect(dateDispo, SIGNAL(dateChanged(QDate)), sauver, SLOT(activerButton()));
    QObject::connect(dateEcheance, SIGNAL(dateChanged(QDate)), sauver, SLOT(activerButton()));
    QObject::connect(dureeH, SIGNAL(dateChanged(QDate)), sauver, SLOT(activerButton()));
    QObject::connect(dureeM, SIGNAL(dateChanged(QDate)), sauver, SLOT(activerButton()));
    QObject::connect(dateDispo, SIGNAL(dateChanged(QDate)), sauver, SLOT(verifierDate()));
    QObject::connect(dateEcheance, SIGNAL(dateChanged(QDate)), sauver,SLOT(verifierDate()));



}

void TacheEditeur::sauverTache()
{
    TacheManager& m = TacheManager::getInstance();
    if(m.isTacheExistante(idLineEdit->text()) && &m.getTache(idLineEdit->text()) != &t)
    {
        QMessageBox::warning(this, "ATTENTION", "Tache deja existante");
        return;
    }
    t.setTitre(titreLineEdit->text());
    t.setDatesDisponibiliteEcheance(dateDispo->date(), dateEcheance->date());
    t.setDuree(Duree(dureeH->value(), dureeM->value()));
    if(preemtive->isChecked()) t.setPreemptive();
    else t.setNonPreemptive();
    QMessageBox::information(this, "sauvegarde", "Tache a bien ete sauvegardee");
}

void TacheEditeur::activerButton()
{
    sauver->setEnabled(true);
}

void TacheEditeur::verifierDate()
{
    if(dateEcheance->date().daysTo(dateDispo->date())>0)
    {
        QMessageBox::warning(this, "date anterieure", "probleme date");
    }

}

TacheEditeur::~TacheEditeur()
{
}

