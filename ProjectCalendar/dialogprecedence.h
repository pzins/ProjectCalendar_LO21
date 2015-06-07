#ifndef DIALOGPRECEDENCE_H
#define DIALOGPRECEDENCE_H

#include <QDialog>
#include "projetmanager.h"
#include "precedencemanager.h"

namespace Ui {
class DialogPrecedence;
}


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
    void chargerProjets();
    void setItemTache(QStandardItem* i){item_tache = i;}
    void chargerAnterieure();
    void testDejaProg(Tache *ant, Tache *post);
};

#endif // DIALOGPRECEDENCE_H
