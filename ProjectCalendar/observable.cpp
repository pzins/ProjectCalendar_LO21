#include "observable.h"

void Observable::ajouterObservateur(Observateur* o)
{
    obs.insert(o);
}

void Observable::supprimerObservateur(Observateur* o)
{
    obs.erase(o);
}


