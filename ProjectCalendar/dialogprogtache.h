#ifndef DIALOGPROGTACHE_H
#define DIALOGPROGTACHE_H
#include <QDialog>
#include "projet.h"

namespace Ui {
class DialogProgTache;
}

class DialogProgTache : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgTache(TacheUnitaire* tache_, Projet* projet_, QWidget *parent = 0);
    ~DialogProgTache();
    static DialogProgTache& getInstance(TacheUnitaire* tache_, Projet* projet_, QWidget* parent = 0);
    static void libererInstance();
    void verification();
    void setTache(TacheUnitaire* t){tache = t;}
    void setProjet(Projet* p){projet= p;}

public slots:
    void accept();

private:
    Ui::DialogProgTache *ui;
    static DialogProgTache* instance;
    Projet* projet;
    TacheUnitaire* tache;

};

#endif // DIALOGPROGTACHE_H
