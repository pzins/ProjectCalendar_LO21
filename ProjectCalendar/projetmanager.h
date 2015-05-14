#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include <QString>
#include "projet.h"


class ProjetManager
{
    friend class Projet;

private:
    std::map<QString, Projet*> map_projet;
    ProjetManager(){}
    ~ProjetManager(){}
    ProjetManager(const ProjetManager& p){}
    ProjetManager& operator=(const ProjetManager& p){}

    static ProjetManager* instance;


public:

    static ProjetManager& getInstance(){
        if(!instance) instance = new ProjetManager();
        return *instance;
    }

    static void libererInstance(){
        delete instance;
    }
    bool ajouterProjet(const QString& id, const QString& titre, const QDate& dispo,const QDate& echeance);

};

#endif // PROJETMANAGER_H
