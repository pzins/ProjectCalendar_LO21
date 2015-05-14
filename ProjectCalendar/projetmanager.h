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
    void retirerProjet(const QString& id);

    const std::map<QString, Projet*>& getMapProjet() const {return map_projet;}
    Projet& getProjet(const QString& id);


    class Iterator
    {
    private:
        friend class ProjetManager;
        std::map<QString, Projet*>::iterator courant;
        Iterator(std::map<QString, Projet*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0){}
        Projet* operator*() const {return courant->second;}
        Iterator& operator++(){++courant; return *this;}
        Iterator operator++(int i){
            Iterator old = *this;
            ++courant;
            return old;
        }
        bool operator==(Iterator it) const{
            return courant == it.courant;
        }
        bool operator!=(Iterator it) const{
            return courant != it.courant;
        }
    };

    Iterator begin(){return Iterator(map_projet.begin());}
    Iterator end(){return Iterator(map_projet.end());}

};

#endif // PROJETMANAGER_H
