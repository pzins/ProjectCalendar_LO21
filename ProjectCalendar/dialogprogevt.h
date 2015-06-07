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


    Ui::DialogProgEvt *ui;


public slots:
    void accept();
    void adaptForm(bool etat);
    void isReunion(bool etat);


public:
    explicit DialogProgEvt(QWidget *parent = 0);
    ~DialogProgEvt();

};

#endif // DIALOGPROGEVT_H
