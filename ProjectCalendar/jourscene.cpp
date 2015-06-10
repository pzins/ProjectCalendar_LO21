#include "jourscene.h"
#include "agenda.h"
#include <QGraphicsLineItem>


void JourScene::ajouterProgrammation(const QString titre, const QTime& debut, const Duree& duree,
        Programmation* p, int type)
{
    int mins_ecoulees = -debut.secsTo(QTime(8,0)) / 60;
    QTime fin = debut;
    fin = fin.addSecs(duree.getDureeEnMinutes() * 60);

    qreal y = ( height() / minutes ) * mins_ecoulees;
    qreal h = ( height() / minutes ) * duree.getDureeEnHeures()*60;


    //création et ajout de l'item à la scene
    ProgrammationItem* prog = new ProgrammationItem(0,y,width(),h,p);
    prog->setPen(QPen(vec_couleur[type].fond));
    prog->setBrush(QBrush(vec_couleur[type].fond));
    QGraphicsScene::addItem(prog);
    prog->setFlag(QGraphicsItem::ItemIsSelectable);
    prog->setZValue(1);

    //affichage de l'horaire et du titre en fonction de la taille de la case
    int Xtxt = 0,Ytxt = y;
    QString s;
    if(duree.getDureeEnMinutes()<30)
        return;
    else if(duree.getDureeEnMinutes()<45)
    {
        Xtxt = -3;
        Ytxt = y - 3;
        s = debut.toString("hh:mm") + "   -   " + fin.toString("hh:mm");
    }else if(duree.getDureeEnMinutes() >= 45)
        s = debut.toString("hh:mm") + "   -   " + fin.toString("hh:mm") + "\n" + titre;
    else
        s = debut.toString("hh:mm") + "   -   " + fin.toString("hh:mm");

    QGraphicsTextItem *txt = QGraphicsScene::addText(s,QFont("Helvetica",9,QFont::Black));
    txt->setTextWidth(95);
    txt->setX(Xtxt);
    txt->setY(Ytxt);
    txt->setZValue(2);
}




void JourScene::dessinerFond()
{
    //r : taille des espaces entre les traits : 1 trait toutes les  30 min
    qreal r = (height() / minutes)*30;
    qreal x = 0;
    int i = 0;    
    while( x < minutes)
    {
        //un trait sur 2 sera plein (à chaque heure)
        //l'autre sera en pointillé : (à chaque demie heure)
        if(i % 2 == 0)
        {
            i=0;
            QGraphicsScene::addLine(-2,x,width()+2,x,QPen(Qt::gray,1,Qt::PenStyle(Qt::SolidLine)))->setZValue(0);
        }
        else
        {
            QGraphicsScene::addLine(-2,x,width()+2,x,QPen(Qt::gray,1,Qt::PenStyle(Qt::DashDotLine)))->setZValue(0);
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
    //parcours et suppression de tous les items ajoutés à la scene
    while(iter != end)
    { QGraphicsItem* item = (*iter); this->removeItem(item); iter++; }

}

void JourScene::update(const QString& s1, const QString& s2)
{
    //on vide d'abord la scene
    removeAllItems();
    //on dessine le fond
    dessinerFond();
    Agenda* ag = &Agenda::getInstance();
    //on parcourt toutes les programmations de l'agenda
    for(Agenda::Iterator it = ag->begin() ; it != ag->end() ; ++it)
    {
        //si c'est un évènement sur plusieurs jours
        if((*it).type() == 4)
        {
            ProgrammationEvenementplsJ* p = dynamic_cast<ProgrammationEvenementplsJ*>(&*it);
            QDate deb = p->getDate(), fin = p->getDateFin();
            //si la date de la scène correspond au début de la programmation
            if(date == deb)
            {
                int nb_mins = p->getDebut().secsTo(QTime(22,0)) / 60;
                ajouterProgrammation(p->getTitre(),p->getDebut(),Duree(nb_mins),p, (*it).type());
            }
            //si la date de la scene est inclue dans la programmation
            else if(date<fin && date>deb)
            {
                ajouterProgrammation(p->getTitre(),QTime(8,0),Duree(14,0),p, (*it).type());
            }
            //si la date de la scène correspond à la fin de la programmation
            else if(date == fin)
            {
                int nb_mins = QTime(8,0).secsTo(p->getFin()) / 60;
                ajouterProgrammation(p->getTitre(),QTime(8,0),Duree(nb_mins),p, (*it).type());
            }
        }
        //sinon si la date de la programmation correspond à la date de la scène
        else if((*it).getDate() == date)
        {
            Duree d = (*it).getDuree();
            ajouterProgrammation((*it).getTitre(), (*it).getDebut(),d, &*it, (*it).type());
        }
    }
}



