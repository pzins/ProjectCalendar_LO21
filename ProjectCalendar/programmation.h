#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include <QDate>
#include <QTime>
#include <iostream>

class Programmation {
    QDate date;
    QTime debut;

public:
    Programmation(const QDate& date_, const QTime& debut_): date(date_), debut(debut_){}
    QDate getDate() const {return date;}
    QTime getDebut() const {return debut;}
   // const Tache& getTache() const =0;
    virtual void afficher() const =0;
};


#endif // PROGRAMMATION_H
