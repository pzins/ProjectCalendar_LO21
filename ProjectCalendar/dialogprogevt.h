#ifndef DIALOGPROGEVT_H
#define DIALOGPROGEVT_H

#include <QDialog>

namespace Ui {
class DialogProgEvt;
}

class DialogProgEvt : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgEvt(QWidget *parent = 0);
    ~DialogProgEvt();


    Ui::DialogProgEvt *ui;
    static DialogProgEvt* instance;


public slots:
    void accept();
    void adaptForm(bool etat);
    void isReunion(bool etat);


public:
    static DialogProgEvt& getInstance(QWidget* parent = 0);
    static void libererInstance();

};

#endif // DIALOGPROGEVT_H
