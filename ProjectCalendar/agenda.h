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



};

#endif // AGENDA_H
