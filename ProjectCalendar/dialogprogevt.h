#ifndef DIALOGPROGEVT_H
#define DIALOGPROGEVT_H

#include <QDialog>
#include <QDate>
namespace Ui {
class DialogProgEvt;
}

/**
 * @class DialogProgEvt
 * @brief Fenêtre pour la programmation d'évènement
 */
class DialogProgEvt : public QDialog
{
    Q_OBJECT

public:
    Ui::DialogProgEvt *ui;

public slots:
    /**
     * @brief accept : va faire les vérifications de contriaintes et l'ajout de la programmations
     * si les contraintes il n'y a pas d'erreur
     */
    void accept();

    /**
     * @brief adaptForm : adapte le formulaire en fonction de l'évènement à ajouter
     * @param etat
     */
    void adaptForm(bool etat);

    /**
     * @brief isReunion : adapte le formulaire si l'évènement est un rendez-vous
     * @param etat
     */
    void isRdv(bool etat);

    /**
     * @brief adaptTimeDebut : adapte les champs Time et Date début
     * @param d
     */
    void adaptTimeDebut(QDate d);

    /**
     * @brief adaptTimeFin : adapte les champs Time et Date fin
     * @param d
     */
    void adaptTimeFin(QDate d);


public:
    explicit DialogProgEvt(QWidget *parent = 0);
    ~DialogProgEvt();

};

#endif // DIALOGPROGEVT_H
