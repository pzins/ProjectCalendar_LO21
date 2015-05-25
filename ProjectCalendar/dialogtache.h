#ifndef DIALOGTACHE_H
#define DIALOGTACHE_H

#include <QDialog>
#include "projetmanager.h"

namespace Ui {
class DialogTache;
}

class DialogTache : public QDialog
{
    Q_OBJECT

public:
    static DialogTache& getInstance(QWidget* parent = 0);
    static void libererInstance();
    void afficherProjets();

public slots:
    void autoriserDuree(bool etat);
    void valider();
    void afficherComposite(QString titre);


private:
    explicit DialogTache(QWidget *parent = 0);
    ~DialogTache();
    DialogTache& operator=(const DialogTache&);
    DialogTache(const DialogTache&);

    Ui::DialogTache *ui;
    static DialogTache* instance;
    ProjetManager* pm;

};

#endif // DIALOGTACHE_H
