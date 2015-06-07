#ifndef JOURSCENE_H
#define JOURSCENE_H
#include <QGraphicsScene>
#include <QDate>
#include "duree.h"
#include "programmation.h"
#include "programmationitem.h"
#include "programmationevenementplsj.h"
#include "observateur.h"

struct Couleur
{
    QColor contour;
    QColor fond;
};



class JourScene : public QGraphicsScene, public Observateur
{
private:
    QString jour;
    QDate date;
    unsigned int minutes;
    Couleur vec_couleur[5];

public:
    JourScene(const QString& nom_, const QDate& date_, qreal x_, qreal y_, qreal width_, qreal height_,
              unsigned int minutes_ = 840, QObject* parent = 0 )
        :  QGraphicsScene(x_,y_,width_,height_,parent),jour(nom_),date(date_), minutes(minutes_)
    {
        vec_couleur[0] = {QColor("black"),QColor("red")};
        vec_couleur[1] = {QColor("black"),QColor("orange")};
        vec_couleur[2] = {QColor("black"),QColor("lightgreen")};
        vec_couleur[3] = {QColor("black"),QColor("yellow")};
        vec_couleur[4] = {QColor("black"),QColor("lightblue")};

        dessinerFond();
    }

    const QDate& getDate() const {return date;}
    void setDate(QDate& d) {date = d;}

    void ajouterProgrammation(const QString titre, const QTime& debut, const Duree& duree,
            Programmation* e=0, int type=0);
    void dessinerFond();

    void removeAllItems();

    virtual void update(const QString& s1="", const QString& s2="");

};

#endif // JOURSCENE_H
