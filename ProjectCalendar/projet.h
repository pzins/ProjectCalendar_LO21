#ifndef PROJET_H
#define PROJET_H
#include "tache.h"
#include <QString>

class Projet
{
private:
    QString id;
    QString titre;
    QDate dispo;
    QDate echeance;
    std::map<QString, Tache*> vect_tache;

public:
    Projet(const QString& id_, const QString& titre_, const QDate& dispo_, const QDate& echeance_) :
        id(id_), titre(titre_), dispo(dispo_), echeance(echeance_){}
    ~Projet();
};

#endif // PROJET_H
