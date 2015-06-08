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

    void ajouterObservateur(Observateur*);
    void supprimerObservateur(Observateur*);

    /**
     * @brief notifier : notifie tous les observateurs qui vont se mettre à jour
     * @param s1 parametre optionel
     * @param s2 parametre optionel
     */
    virtual void notifier(const QString& s1="", const QString& s2="") =0;

    const std::set<Observateur*>& getObs() const {return obs;}

    /**
     * @class Iterator
     * @brief Iterator sur tous les observateurs
     */
    class Iterator
    {
    private:
        std::set<Observateur*>::iterator courant;
    public:
        Iterator(std::set<Observateur*>::iterator deb) : courant(deb){}
        Observateur& operator*() const {return **courant;}
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

    Iterator begin(){return Iterator(obs.begin());}
    Iterator end(){return Iterator(obs.end());}
};

#endif // OBSERVABLE_H
