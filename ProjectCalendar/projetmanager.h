#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include "projet.h"

#include <QString>
#include <QPushButton>
#include <QStandardItemModel>



class ProjetManager
{
private:
    std::map<unsigned int, Projet*> map_projet;
    ProjetManager(){}
    ~ProjetManager(){}
    ProjetManager(const ProjetManager& p){}
    ProjetManager& operator=(const ProjetManager& p){}

    static ProjetManager* instance;
    static unsigned int nb_projet;
    QPushButton* button;

    QStandardItemModel model;



public:

    static ProjetManager& getInstance(){
        if(!instance) instance = new ProjetManager();
        return *instance;
    }

    static void libererInstance(){
        delete instance;
    }
    void ajouterProjet(const QString& titre, const QDate& dispo,const QDate& echeance);
    void retirerProjet(Projet& projet);

    const std::map<unsigned int, Projet*>& getMapProjet() const {return map_projet;}
   Projet& getProjet(unsigned int id);

    QStandardItemModel& getModel(){return model;}
    void remplirModel();

    class Iterator
    {
    private:
        friend class ProjetManager;
        std::map<unsigned int, Projet*>::iterator courant;
        Iterator(std::map<unsigned int, Projet*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0){}
        Projet& operator*() const {return *courant->second;}
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
