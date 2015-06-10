#ifndef PROGRAMMTIONITEM_H
#define PROGRAMMTIONITEM_H
#include <QGraphicsRectItem>
#include "programmation.h"

/**
 * @class ProgrammationItem
 * @brief Item représentant une programmation dans le calendrier
 */
class ProgrammationItem : public QGraphicsRectItem
{
private:
    Programmation* prog;
public:
    /**
     * @brief ProgrammationItem
     * @param x position x
     * @param y position y
     * @param width largeur
     * @param height hauteur
     * @param p programmation concernée
     */
    ProgrammationItem(int x,int y,int width,int height, Programmation* p) :
        QGraphicsRectItem(x,y,width,height,0), prog(p) {}

    Programmation* getProgrammation() const {return prog;}
};

#endif // PROGRAMMTIONITEM_H
