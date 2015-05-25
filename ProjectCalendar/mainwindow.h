#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDirModel>
#include <QStandardItemModel>

#include "projetmanager.h"
#include "agenda.h"
#include "dialogprojet.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow& getInstance(QWidget* parent = 0);
    static void libererInstance();

    void afficher_projets(QStandardItemModel& m);
    void afficher_taches(QStandardItem* i, Projet &p);

public slots:
    void nouveauProjet();


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
