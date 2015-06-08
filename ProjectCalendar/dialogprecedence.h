#ifndef DIALOGPRECEDENCE_H
#define DIALOGPRECEDENCE_H

#include <QDialog>
#include "projetmanager.h"
#include "precedencemanager.h"

namespace Ui {
class DialogPrecedence;
}


/**
 * @class DialogPrecedence
 * @brief Fenêtre de dialogue pour l'ajout de précédences
 */
class DialogPrecedence : public QDialog
{
    Q_OBJECT

private:

    Ui::DialogPrecedence *ui;
    QStandardItem* item_tache;

public slots:
    virtual void accept();

public:
    explicit DialogPrecedence(QStandardItem *it, QWidget *parent = 0);
    ~DialogPrecedence();

    void setItemTache(QStandardItem* i){item_tache = i;}
    /**
     * @brief chargerAnterieure : charge les tâches pouvant avoir la contrainte de précédences
     */
    void chargerAnterieure();
    /**
     * @brief testDejaProg : test si l'ajout de précédence ne concerne pas une tâche déjà programmée
     * @param ant tache antérieure
     * @param post tache de base pour laquelle on ajoute une contrainte de précédence
     */
    void testDejaProg(Tache *ant, Tache *post);
};

#endif // DIALOGPRECEDENCE_H
