#ifndef JOURSCENE_H
#define JOURSCENE_H
#include <QGraphicsScene>
#include <QDate>
#include "duree.h"
#include "programmation.h"

class JourScene : public QGraphicsScene
{
private:
    QString jour;
    QDate date;
    unsigned int minutes;

public:
    JourScene(const QString& nom_, const QDate& date_, qreal x_, qreal y_, qreal width_, qreal height_,
              unsigned int minutes_ = 840, QObject* parent = 0 )
        :  QGraphicsScene(x_,y_,width_,height_,parent),jour(nom_),date(date_), minutes(minutes_) {dessinerFond();}

    const QDate& getDate() const {return date;}
    void setDate(QDate& d) {date = d;}

    QGraphicsRectItem *ajouterProgrammation(const QString titre, const QTime& debut, const Duree& duree,
            Programmation* e=0, const QColor& contour = QColor("lightGray"), const QColor& fond = QColor("blue"));
    void dessinerFond();
    void miseAJour();
};

#endif // JOURSCENE_H
