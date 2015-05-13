#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include <QString>
#include "projet.h"


class ProjetManager
{
private:
    std::map<QString, Projet> vect_projet;
    ProjetManager(){};
    ~ProjetManager(){};
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

};

#endif // PROJETMANAGER_H
