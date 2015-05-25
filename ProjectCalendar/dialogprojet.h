#ifndef DIALOGPROJET_H
#define DIALOGPROJET_H

#include <QDialog>

#include "projetmanager.h"

namespace Ui {
class DialogProjet;
}

class DialogProjet : public QDialog
{
    Q_OBJECT

public:
    static DialogProjet& getInstance(QWidget* parent = 0);
    static void libererInstance();

public slots:
    void valider();


private:
    explicit DialogProjet(QWidget *parent = 0);
    ~DialogProjet();
    DialogProjet& operator=(const DialogProjet&);
    DialogProjet(const DialogProjet&);

    Ui::DialogProjet *ui;
    static DialogProjet* instance;
    ProjetManager* pm;

};

#endif // DIALOGPROJET_H
