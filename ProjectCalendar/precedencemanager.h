#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include <vector>
#include "precedence.h"

class PrecedenceManager
{
private:
    std::vector<Precedence*> vect_precedence;

    PrecedenceManager(){}
    ~PrecedenceManager();
    PrecedenceManager(const PrecedenceManager& p){}
    PrecedenceManager& operator=(const PrecedenceManager& p){}

    static PrecedenceManager* instance;


public:
    void ajouterPrecedence(Tache& pred_, Tache& succ_);
    void retirerPrecedence(Precedence& precedence);

    std::vector<Precedence*> getVectPrecedence() const {return vect_precedence;}

    static PrecedenceManager& getInstance(){
        if(!instance) instance = new PrecedenceManager();
        return *instance;
    }

    static void liberer_instance(){
        delete instance;
    }




    class Iterator
    {
    private:
        friend class PrecedenceManager;
        std::vector<Precedence*>::iterator courant;
        Iterator(std::vector<Precedence*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0) {}
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

    Iterator begin(){return Iterator(vect_precedence.begin());}
    Iterator end(){return Iterator(vect_precedence.end());}
};

#endif // PRECEDENCEMANAGER_H
