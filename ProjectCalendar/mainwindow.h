#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDirModel>
#include <QStandardItemModel>

#include "projetmanager.h"
#include "agenda.h"
#include "dialogprecedence.h"
#include "precedencemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Observateur
{
    Q_OBJECT

public:
    static MainWindow& getInstance(QWidget* parent = 0);
    static void libererInstance();
    void supprimerAllItem();
    virtual void update(const QString& s1="", const QString& s2="");

public slots:
    void sauvegarder();
    void charger();
    void supprimerItem();
    void adaptForm(bool etat);
    void adaptForm2(bool etat);
    void ajouter();
    void afficherInfo(QModelIndex idx);
    void ajouterPrecedence();
    void expand();
    void supprimer_precedence();
    void test();



private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow& operator=(const MainWindow&);
    MainWindow(const MainWindow&);

    Ui::MainWindow *ui;
    static MainWindow* instance;

    ProjetManager* pm;
    PrecedenceManager* pre;
    Agenda* ag;



};




#endif // MAINWINDOW_H
