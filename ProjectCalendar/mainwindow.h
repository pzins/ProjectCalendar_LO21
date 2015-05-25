#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDirModel>
#include <QStandardItemModel>

#include "projetmanager.h"
#include "agenda.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow& getInstance(QWidget* parent = 0);
    static void deleteInstance();

public slots:


private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow& operator=(const MainWindow&);
    MainWindow(const MainWindow&);

    Ui::MainWindow *ui;
    static MainWindow* mw;

    ProjetManager* pm;
    Agenda* ag;

    QPushButton* b;
    QStandardItemModel* model;

};

#endif // MAINWINDOW_H
