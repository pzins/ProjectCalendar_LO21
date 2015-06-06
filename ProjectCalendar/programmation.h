#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include <QDate>
#include <QTime>
#include "duree.h"
#include <iostream>

class Programmation {
    QDate date;
    QTime debut;

public:
    Programmation(const QDate& date_, const QTime& debut_): date(date_), debut(debut_){}

    virtual ~Programmation(){}

    QDate getDate() const {return date;}
    QTime getDebut() const {return debut;}
    virtual const Duree& getDuree() const =0;
   // const Tache& getTache() const =0;
    virtual void afficher() const =0;

    virtual const QString& getTitre() const =0;
    virtual const QString& getDescription() const =0;
    virtual const QString toString() const;
    virtual bool isEvtPlsJ() const =0;


};


#endif // PROGRAMMATION_H
