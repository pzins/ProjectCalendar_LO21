//#ifndef DIALOGTACHE_H
//#define DIALOGTACHE_H

//#include <QDialog>
//#include "projetmanager.h"
//#include "observateur.h"



//namespace Ui {
//class DialogTache;
//}

//class DialogTache : public QDialog, public Observateur
//{
//    Q_OBJECT

//private:
//    explicit DialogTache(QWidget *parent = 0);
//    ~DialogTache();
//    DialogTache& operator=(const DialogTache&);
//    DialogTache(const DialogTache&);

//    Ui::DialogTache *ui;
//    static DialogTache* instance;
//    ProjetManager* pm;

//    std::set<Observateur*> obs;
//public:
//    static DialogTache& getInstance(QWidget* parent = 0);
//    static void libererInstance();
//    void afficherProjets();

//    virtual void ajouterObservateur(Observateur* o);
//    virtual void supprimerObservateur(Observateur* o);
//    virtual void notifier();
//    virtual void update();

//public slots:
//    void updateDuree(bool etat);
//    void valider();
//    void updateComposite(QString titre);



//};

//#endif // DIALOGTACHE_H
