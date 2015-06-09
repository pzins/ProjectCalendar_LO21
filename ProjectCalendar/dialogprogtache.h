#ifndef DIALOGPROGTACHE_H
#define DIALOGPROGTACHE_H
#include <QDialog>
#include "projet.h"

namespace Ui {
class DialogProgTache;
}

/**
 * @class DialogProgTache
 * @brief Fenêtre pour la programamtion de tâche
 */
class DialogProgTache : public QDialog
{
    Q_OBJECT
private:
    Ui::DialogProgTache *ui;
    Projet* projet;
    TacheUnitaire* tache;

    std::vector<QString> vec_titre;
    std::vector<QDate> vec_date;
    std::vector<QTime> vec_debut;
    std::vector<Duree> vec_duree;

public:
    explicit DialogProgTache(TacheUnitaire* tache_, Projet* projet_, QWidget *parent = 0);
    ~DialogProgTache();

    /**
     * @brief verification : vérification de la programmation par rapport aux précédences, disponibilités, échéances,...
     */
    void verification();
    /**
     * @brief verificationParties : vérifications de la programmations des parties de la tâche
     */
    void verificationParties();

    void setTache(TacheUnitaire* t){tache = t;}
    void setProjet(Projet* p){projet= p;}

public slots:
    void accept();
    /**
     * @brief adaptForm : adapte le formulaire si on veut programmer des parties
     * @param etat
     */
    void adaptForm(bool etat);
    /**
     * @brief ajouterParties : ouvre la fenêtre DialogProgTache si l'on veut programmer des parties de tâches
     */
    void ajouterParties();

    void adaptTime(QDate d);

};

#endif // DIALOGPROGTACHE_H
