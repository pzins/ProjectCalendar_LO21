#include "jourscene.h"
#include "agenda.h"
#include <QGraphicsLineItem>


void JourScene::ajouterProgrammation(const QString titre, const QTime& debut, const Duree& duree,
        Programmation* p, const QColor& contour, const QColor& fond)
{
    int mins_ecoulees = -debut.secsTo(QTime(8,0)) / 60;
    QTime fin = debut;
    fin = fin.addSecs(duree.getDureeEnMinutes() * 60);

    qreal y = ( height() / minutes ) * mins_ecoulees;
    qreal h = ( height() / minutes ) * duree.getDureeEnHeures()*60;

    ProgrammationItem* prog = new ProgrammationItem(0,y,width(),h,p);
    prog->setPen(QPen(contour));
    prog->setBrush(QBrush(fond));

    QGraphicsScene::addItem(prog);
    prog->setFlag(QGraphicsItem::ItemIsSelectable);
    prog->setZValue(1);

    int Xtxt = 0,Ytxt = y;
    QString s;
    if(duree.getDureeEnMinutes()<30)
        return;
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
}



//8h-22h : 840min
void JourScene::dessinerFond()
{
    qreal r = (height() / minutes)*30;
    qreal x = 0;
    int i = 0;
    while( x < minutes)
    {
        if(i % 2 == 0)
        {
            i=0;
            QGraphicsScene::addLine(0,x,width(),x,QPen(QColor("lightBlue"),1,Qt::PenStyle(Qt::SolidLine)))->setZValue(0);
        }
        else
        {
            QGraphicsScene::addLine(0,x,width(),x,QPen(QColor("lightGray"),1,Qt::PenStyle(Qt::DashDotLine)))->setZValue(0);
        }
        x += r;
        ++i;
    }
}

void JourScene::removeAllItems()
{
    QList<QGraphicsItem*> itemsList = this->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end)
    { QGraphicsItem* item = (*iter); this->removeItem(item); iter++; }

}

void JourScene::update(const QString& s1, const QString& s2)
{
    removeAllItems();
    dessinerFond();
    Agenda& a = Agenda::getInstance();
    for(Agenda::Iterator it = a.begin() ; it != a.end() ; ++it)
    {
        if((*it).isEvtPlsJ())
        {
            ProgrammationEvenementplsJ* p = dynamic_cast<ProgrammationEvenementplsJ*>(&*it);
            a.ajouterProgrammationPlsJour(p);
        }
        else if((*it).getDate() == date)
        {
            ajouterProgrammation((*it).getTitre(), (*it).getDebut(),(*it).getDuree(), &*it);
        }
    }
}


