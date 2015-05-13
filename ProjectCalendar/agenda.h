#ifndef AGENDA_H
#define AGENDA_H
#include <vector>
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



};

#endif // AGENDA_H
