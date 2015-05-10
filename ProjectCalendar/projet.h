#ifndef PROJET_H
#define PROJET_H
#include "tache.h"
#include <QString>

class Projet
{
private:
    QString nom;
    std::map<QString, Tache*> vect_tache;

public:
    Projet();
    ~Projet();
};

#endif // PROJET_H
