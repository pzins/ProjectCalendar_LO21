#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow* MainWindow::mw = 0;

MainWindow& MainWindow::getInstance(QWidget* parent)
{
    if(mw) return *mw;
    else{
        mw = new MainWindow(parent);
        return *mw;
    }
}

void MainWindow::deleteInstance()
{
    delete mw;
    mw = 0;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pm = &ProjetManager::getInstance();
    ag = &Agenda::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}
