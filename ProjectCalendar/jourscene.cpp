#include "jourscene.h"
#include "agenda.h"
#include <QGraphicsLineItem>
#include "programmationitem.h"


QGraphicsRectItem* JourScene::ajouterProgrammation(const QString titre, const QTime& debut, const Duree& duree,
        Programmation* e, const QColor& contour, const QColor& fond)
{
    //std::cout << "-------------********** EVT = "<<e->getDate().toString().toStdString()<<"\n";
    int mins_ecoulees = -debut.secsTo(QTime(6,0)) / 60;
    QTime fin = debut;
    fin = fin.addSecs(duree.getDureeEnMinutes() * 60);

    qreal y = ( height() / minutes ) * mins_ecoulees;
    qreal h = ( height() / minutes ) * duree.getDureeEnHeures()*60;

    //QGraphicsRectItem *rect = new QGraphicsRectItem(0,y,largeur,h,0);
    //QGraphicsRectItem *rect =  QGraphicsScene::addRect(0-3,y,largeur+6,h,QPen(coul_contour),QBrush(coul_fond));
    ProgrammationItem *tache = new ProgrammationItem(-3,y,width()+6,h,e);
    tache->setPen(QPen(contour));
    tache->setBrush(QBrush(fond));
    //TacheGraphicItem *rect =  JourGraphicScene::addRect(tache,QPen(coul_contour),QBrush(coul_fond));
    QGraphicsScene::addItem(tache);

    tache->setFlag(QGraphicsItem::ItemIsSelectable);
    //rect->setFlag(QGraphicsItem::ItemIsFocusable);

    tache->setZValue(1);


    int Xtxt = 0,Ytxt = y;
    QString s;
    if(duree.getDureeEnMinutes()<30)
        return 0;
    else if(duree.getDureeEnMinutes()<75)
    {
        Xtxt = -3;
        Ytxt = y - 3;
        s = debut.toString("hh:mm") + "   -   " + fin.toString("hh:mm");
    }else if(duree.getDureeEnMinutes() >= 75)
        s = debut.toString("hh:mm") + "   -   " + fin.toString("hh:mm") + "\n" + titre;
    else
        s = debut.toString("hh:mm") + "   -   " + fin.toString("hh:mm");


    QGraphicsTextItem *txt = QGraphicsScene::addText(s,QFont("Helvetica",8));
    txt->setTextWidth(95);
    txt->setX(Xtxt);
    txt->setY(Ytxt);
    txt->setZValue(2);
    return tache;






}
/*
QGraphicsRectItem* JourScene::ajouterEvenement(const QString titre, const QTime &deb, const Duree &dur,Evenement*e, const QColor& coul_contour, const QColor& coul_fond)
{
    //std::cout << "-------------********** EVT = "<<e->getDate().toString().toStdString()<<"\n";
    int mins_ecoulees = -deb.secsTo(QTime(6,0)) / 60;
    QTime fin = deb;
    fin = fin.addSecs(dur.getDureeEnMinutes() * 60);

    qreal y = ( hauteur / nb_minutes ) * mins_ecoulees;
    qreal h = ( hauteur / nb_minutes ) * dur.getDureeEnHeures()*60;

    //QGraphicsRectItem *rect = new QGraphicsRectItem(0,y,largeur,h,0);
    //QGraphicsRectItem *rect =  QGraphicsScene::addRect(0-3,y,largeur+6,h,QPen(coul_contour),QBrush(coul_fond));
    EvenementGraphicItem *tache = new EvenementGraphicItem(-3,y,largeur+6,h,e);
    tache->setPen(QPen(coul_contour));
    tache->setBrush(QBrush(coul_fond));
    //TacheGraphicItem *rect =  JourGraphicScene::addRect(tache,QPen(coul_contour),QBrush(coul_fond));
    QGraphicsScene::addItem(tache);

    tache->setFlag(QGraphicsItem::ItemIsSelectable);
    //rect->setFlag(QGraphicsItem::ItemIsFocusable);

    tache->setZValue(1);


    int Xtxt = 0,Ytxt = y;
    QString s;
    if(dur.getDureeEnMinutes()<30)
        return 0;
    else if(dur.getDureeEnMinutes()<75)
    {
        Xtxt = -3;
        Ytxt = y - 3;
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm");
    }else if(dur.getDureeEnMinutes() >= 75)
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm") + "\n" + titre;
    else
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm");


    QGraphicsTextItem *txt = QGraphicsScene::addText(s,QFont("Helvetica",8));
    txt->setTextWidth(95);
    txt->setX(Xtxt);
    txt->setY(Ytxt);
    txt->setZValue(2);
    return tache;
}
*/



//8h-22h : 840min
void JourScene::dessinerFond()
{
    qreal r = (height() / minutes)*30;
    std::cout << height() << " " << minutes << std::endl;
    qreal x = 0;
    int i = 0;
    while( x < minutes)
    {
        if(i % 2 == 0)
        {
            i=0;
            QGraphicsScene::addLine(0,x,width(),x,QPen(QColor("red"),1,Qt::PenStyle(Qt::SolidLine)))->setZValue(0);
        }
        else
        {
            QGraphicsScene::addLine(0,x,width(),x,QPen(QColor("lightGray"),1,Qt::PenStyle(Qt::DashDotLine)))->setZValue(0);
        }
        x += r;
        ++i;
    }
}


void JourScene::miseAJour()
{
    clear();
    dessinerFond();
    Agenda& ag = Agenda::getInstance();
    for(Agenda::Iterator it = ag.begin() ; it != ag.end() ; ++it)
    {
        if((*it).getDate() == date)
        {
            /*if((*it).isEvt())
            {
                Programmation *prog= dynamic_cast<Programmation*>(&(*it));*/
               // ajouterProgrammtion(evt->getSujet(),(*it).getHoraire(),evt->getDuree(),evt);
           // }
        }
    }
}

