#include <QApplication>
#include "projetmanager.h"
#include "agenda.h"
#include "precedencemanager.h"
#include "mainwindow.h"
#include <QTextStream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //ouverture de la fenêtre principale
    MainWindow& m = MainWindow::getInstance();
    m.show();
    return a.exec();
}
