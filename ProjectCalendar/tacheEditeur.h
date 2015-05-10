#ifndef TACHEEDITEUR_H
#define TACHEEDITEUR_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QDateEdit>
#include "calendar.h"
#include <QMessageBox>

#include "tache.h"


class TacheEditeur : public QWidget
{
private:
    Q_OBJECT
    Tache& t;
    QVBoxLayout *vertical;

   //premiere couche
    QHBoxLayout* couche1;
    QLabel* id;
    QLineEdit* idLineEdit;
    QCheckBox* preemtive;

    //deuxieme couche
    QHBoxLayout* couche2;
    QLabel* titre;
    QLineEdit* titreLineEdit;

    //troisieme couche
    QHBoxLayout* couche3;
    QLabel* dispo, *echeance, *duree;
    QDateEdit *dateDispo, *dateEcheance;
    QSpinBox *dureeH, *dureeM;


    //quatrieme couche
    QHBoxLayout* couche4;
    QPushButton *annuler, *sauver;


public:
    explicit TacheEditeur(Tache& t, QWidget* parent = 0);

    ~TacheEditeur();

signals:


public slots:
    void sauverTache();
    void activerButton();
    void verifierDate();

};

#endif // TACHEEDITEUR_H
