#ifndef AGENDA_H
#define AGENDA_H
#include <vector>
#include <iostream>
#include "tache.h"
#include "programmation.h"


class Agenda {
private:
    std::vector<Programmation*> vect_progr;


    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;

    Agenda();
    ~Agenda();
    Agenda(const Agenda& a);
    Agenda& operator=(const Agenda& a);

    static Agenda* instance;


public:
    void ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h);
    static Agenda& getInstance(){
        if(!instance) instance = new Agenda();
        return *instance;
    }
    static void libererInstance(){delete instance;}

    void ajouterProg(Programmation& p){
        for (int i = 0; i < vect_progr.size(); ++i)
            if(vect_progr[i]->getDate() == p.getDate() && vect_progr[i]->getDebut() == p.getDebut()){
                std::cout << "Ajout de programmation impossible" << std::endl;
                throw CalendarException("2 programmations se chevauchent");
                break;
            }
        vect_progr.push_back(&p);
    }

    class Iterator
    {
    private:
        friend class Agenda;
        std::vector<Programmation*>::iterator courant;
        Iterator(std::vector<Programmation*>::iterator deb) : courant(deb){}
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

    Iterator begin(){return Iterator(vect_progr.begin());}
    Iterator end(){return Iterator(vect_progr.end());}

};

#endif // AGENDA_H
