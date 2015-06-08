#ifndef DIALOGPROGEVT_H
#define DIALOGPROGEVT_H

#include <QDialog>

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

public:
    explicit DialogProgEvt(QWidget *parent = 0);
    ~DialogProgEvt();

};

#endif // DIALOGPROGEVT_H
