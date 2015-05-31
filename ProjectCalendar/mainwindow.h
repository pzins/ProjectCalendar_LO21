#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDirModel>
#include <QStandardItemModel>

#include "projetmanager.h"
#include "agenda.h"
#include "dialogprojet.h"
#include "dialogtache.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow& getInstance(QWidget* parent = 0);
    static void libererInstance();
    void supprimerAllItem();

public slots:
    void sauvegarder();
    void charger();
    void supprimerItem();
    void adaptForm(bool etat);
    void adaptForm2(bool etat);
    void ajouter();
    void afficherInfo(QModelIndex idx);
    void test();
    void expand();




private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow& operator=(const MainWindow&);
    MainWindow(const MainWindow&);

    Ui::MainWindow *ui;
    static MainWindow* instance;

    ProjetManager* pm;
    Agenda* ag;



};




#endif // MAINWINDOW_H
