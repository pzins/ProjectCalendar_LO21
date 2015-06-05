#ifndef AGENDA_H
#define AGENDA_H
#include <vector>
#include <iostream>
#include <set>
#include "tache.h"
#include "programmation.h"

class ProgComp
{
public:
    bool operator()(Programmation* a, Programmation* b)
    {
        return (a->getDate() < b->getDate())||
                (a->getDate() == b->getDate() && a->getDebut() < b->getDebut());
    }
};

class Agenda {
private:
    std::set<Programmation*, ProgComp> set_prog;


    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;

    Agenda();
    ~Agenda();
    Agenda(const Agenda& a);
    Agenda& operator=(const Agenda& a);

    static Agenda* instance;


public:

    static Agenda& getInstance(){
        if(!instance) instance = new Agenda();
        return *instance;
    }
    static void libererInstance(){delete instance;}

    Agenda& operator<<(Programmation& evt);
    Agenda& operator>>(Programmation* evt);

    class Iterator
    {
    private:
        friend class Agenda;
        std::set<Programmation*, ProgComp>::iterator courant;
        Iterator(std::set<Programmation*, ProgComp>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0) {}
        Programmation& operator*() const {return **courant;}
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

    Iterator begin(){return Iterator(set_prog.begin());}
    Iterator end(){return Iterator(set_prog.end());}

};

#endif // AGENDA_H
