#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

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
  //  QPushButton* b = new QPushButton("fekir", this);
    model = new QStandardItemModel(5,3);
    QStandardItem* item = new QStandardItem("nabil fekir");
    model->appendRow(item);
    item->appendRow(new QStandardItem("21 ans"));

    //model->children()
    //model->setReadOnly(false);
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
