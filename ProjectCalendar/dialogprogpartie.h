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
 * @brief Représentation des éléments du formualire pour l'ajout d'une partie de tache
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

    /**
     * @brief DialogProgPartie
     * @param nb
     * @param vec_titre_ vecteur contenant les titres des parties
     * @param vec_date_ vecteur contenant les dates des parties
     * @param vec_debut_ vecteur contenant les horaires de début des parties
     * @param vec_duree_ vecteur contenant les durées des parties
     * @param parent
     */
    explicit DialogProgPartie(int nb, std::vector<QString> &vec_titre_, std::vector<QDate> &vec_date_,
                              std::vector<QTime> &vec_debut_, std::vector<Duree> &vec_duree_, QWidget *parent = 0);
    ~DialogProgPartie();

    /**
     * @brief initialisation : initialise le formulaire en fonctions du nombre de parties
     * @param nb nombre de parties  de tache
     */
    void initialisation(int nb);



public slots:
    /**
     * @brief accept : vérifie des contraintes et réalise l'ajout des programmations de partie de tache dans
     * l'agenda si toutes les parties vérifient les conditions
     */
    void accept();


};

#endif // DIALOGPROGPARTIE_H
