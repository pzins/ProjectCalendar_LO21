#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include <vector>
#include <set>
#include "precedence.h"
#include "observable.h"

class PrecedenceManager : public Observable
{
private:
    std::set<Precedence*> set_precedence;

    PrecedenceManager(){}
    virtual ~PrecedenceManager();
    PrecedenceManager(const PrecedenceManager& p){}
    PrecedenceManager& operator=(const PrecedenceManager& p){}

    static PrecedenceManager* instance;

    std::set<Observateur*> obs;

public:
    std::set<Precedence*> getVectPrecedence() const {return set_precedence;}

    static PrecedenceManager& getInstance(){
        if(!instance) instance = new PrecedenceManager();
        return *instance;
    }

    static void liberer_instance(){
        delete instance;
    }

    void ajouterPrecedence(Tache& pred_, Tache& succ_, Projet& projet_);
    void retirerPrecedence(Precedence& precedence);
    bool contains(const Precedence& p);


    virtual void ajouterObservateur(Observateur* o);
    virtual void supprimerObservateur(Observateur* o);
    virtual void notifier();







    class Iterator
    {
    private:
        friend class PrecedenceManager;
        std::set<Precedence*>::iterator courant;
        Iterator(std::set<Precedence*>::iterator deb) : courant(deb){}
    public:
        //Iterator() : courant() {}
        Precedence& operator*() const {return **courant;}
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

    Iterator begin(){return Iterator(set_precedence.begin());}
    Iterator end(){return Iterator(set_precedence.end());}
};

#endif // PRECEDENCEMANAGER_H
