#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H
#include <set>
#include <QString>



class Observateur
{
public:

    virtual void update(const QString& s1="", const QString& s2="")=0;

};

#endif // OBSERVATEUR_H
