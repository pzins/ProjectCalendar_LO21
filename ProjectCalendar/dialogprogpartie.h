#ifndef DIALOGPROGPARTIE_H
#define DIALOGPROGPARTIE_H

#include <QDialog>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include "duree.h"

/**
 * @class Partie
 * @brief Partie d'une tâche
 */
class Partie
{
public:
    QLineEdit* titre;
    QDateEdit* date;
    QTimeEdit* debut;
    QTimeEdit* duree;
    QLabel* label;
    ~Partie(){

        delete titre;
        delete date;
        delete debut;
        delete duree;
        delete label;
    }

};

namespace Ui {
class DialogProgPartie;
}

/**
 * @class DialogProgPartie
 * @brief Fenetre pour la programmations de partie de tâche
 */
class DialogProgPartie : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogProgPartie *ui;
    std::vector<QString>& vec_titre;
    std::vector<QDate>& vec_date;
    std::vector<QTime>& vec_debut;
    std::vector<Duree>& vec_duree;
    std::vector<Partie*> vec_parties;

public:

    explicit DialogProgPartie(int nb, std::vector<QString> &vec_titre_, std::vector<QDate> &vec_date_,
                              std::vector<QTime> &vec_debut_, std::vector<Duree> &vec_duree_, QWidget *parent = 0);
    ~DialogProgPartie();

    /**
     * @brief initialisation : initialise le formulaire en fonctions du nombre de parties
     * @param nb nombre de parties  de tache
     */
    void initialisation(int nb);

    /**
     * @brief affichage : affichage des champs du formulaire
     */
    void affichage();


public slots:
    void accept();


};

#endif // DIALOGPROGPARTIE_H
