#ifndef PROGRAMMTIONITEM_H
#define PROGRAMMTIONITEM_H
#include <QGraphicsRectItem>
#include "programmation.h"

class ProgrammationItem : public QGraphicsRectItem
{
private:
    Programmation* prog;
public:
    ProgrammationItem(int x,int y,int width,int height, Programmation* p) :
        QGraphicsRectItem(x,y,width,height,0), prog(p) {}
    Programmation* getProgrammtion() const {return prog;}
};

#endif // PROGRAMMTIONITEM_H
