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
    explicit DialogPrecedence(QWidget *parent = 0);
    ~DialogPrecedence();
    DialogPrecedence& operator=(const DialogPrecedence&);
    DialogPrecedence(const DialogPrecedence&);

    Ui::DialogPrecedence *ui;
    static DialogPrecedence* instance;
    ProjetManager* pm;
    PrecedenceManager* pre;

public slots:
    virtual void accept();
    void chargerTaches(QString titre);

public:
    static DialogPrecedence& getInstance(QWidget* parent = 0);
    static void libererInstance();
    void chargerProjets();
    void chargement();

};

#endif // DIALOGPRECEDENCE_H
