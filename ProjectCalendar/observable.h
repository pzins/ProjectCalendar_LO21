#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "observateur.h"

/**
 * @class Observable
 * @brief class abstraite permettant d'être observé par d'autres objets
 */
class Observable
{
private:
    std::set<Observateur*> obs;
public:

    /**
     * @brief ajouterObservateur : ajout d'un observateur à l'élément
     */
    void ajouterObservateur(Observateur*);
    /**
     * @brief supprimerObservateur : suppression d'un observateur à un élément
     */
    void supprimerObservateur(Observateur*);

    /**
     * @brief notifier : notifie tous les observateurs qui vont se mettre à jour
     * @param s1 parametre optionel
     * @param s2 parametre optionel
     */
    virtual void notifier(const QString& s1="", const QString& s2="") const =0;

    const std::set<Observateur*>& getObs() const {return obs;}

    /**
     * @class Iterator
     * @brief Iterator sur tous les observateurs
     */
    class Iterator : public  std::set<Observateur*>::iterator
    {
    public:
        Iterator(std::set<Observateur*>::iterator deb) : std::set<Observateur*>::iterator(deb){}
        Observateur& operator*() const {return *std::set<Observateur*>::iterator::operator *();}
    };

    Iterator begin(){return Iterator(obs.begin());}
    Iterator end(){return Iterator(obs.end());}
};

#endif // OBSERVABLE_H
