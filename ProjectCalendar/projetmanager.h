#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include <QString>
#include "projet.h"


class ProjetManager
{
private:
    std::map<QString, Projet> vect_projet;
public:
    ProjetManager();
    ~ProjetManager();
};

#endif // PROJETMANAGER_H
