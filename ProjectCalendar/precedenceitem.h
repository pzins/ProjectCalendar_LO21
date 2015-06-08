#ifndef PRECEDENCEITEM_H
#define PRECEDENCEITEM_H
#include <QListWidgetItem>
#include "precedence.h"

/**
 * @class PrecedenceItem
 * @brief Item représentant une précédence
 */
class PrecedenceItem : public QListWidgetItem
{
private:
    Precedence* pre;


public:
    PrecedenceItem(const QString& str, Precedence* pre_) : QListWidgetItem(str), pre(pre_){}
    Precedence* getPrecedence() const {return pre;}
};

#endif // PRECEDENCEITEM_H
