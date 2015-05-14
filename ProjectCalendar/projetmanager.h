#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include <QString>
#include "projet.h"


class ProjetManager
{
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
    const std::map<QString, Projet*>& getMapProjet() const {return map_projet;}
    Projet& getProjet(const QString& id);

};

#endif // PROJETMANAGER_H
