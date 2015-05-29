#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "observateur.h"


class Observable
{
public:
    virtual void ajouterObservateur(Observateur*)=0;
    virtual void supprimerObservateur(Observateur*)=0;
    virtual void notifier()=0;

};

#endif // OBSERVABLE_H
