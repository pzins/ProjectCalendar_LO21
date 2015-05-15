#include "agenda.h"

Agenda* Agenda::instance = 0;

Agenda::Agenda(){}

void Agenda::addItem(Programmation* t){
    vect_progr.push_back(t);
}

Programmation* Agenda::trouverProgrammation(const Tache& t)const{
    for(unsigned int i=0; i<vect_progr.size(); i++)
        //if (&t==&vect_progr[i]->getTache()) return vect_progr[i];
    return 0;
}

void Agenda::ajouterProgrammation(Programmation& progr){
    //if (trouverProgrammation(tache)) throw CalendarException("erreur, Agenda, Programmation deja existante");
//    vect_progr.push_back(
    //Programmation* newt=new Programmation(t,d,h);
    //addItem(newt);
}

void Agenda::retirerProgrammation(Programmation& programmation)
{
    for(std::vector<Programmation*>::iterator it = vect_progr.begin(); it != vect_progr.end(); ++it)
        if(&programmation == (*it))
        {
            vect_progr.erase(it);
            break;
        }
}

Agenda::~Agenda(){
    //for(unsigned int i=0; i<vect_progr.size(); i++) delete vect_progr[i];
    for(std::vector<Programmation*>::iterator it = vect_progr.begin(); it != vect_progr.end(); ++it)
        delete *it;
}

/*
Agenda::Agenda(const Agenda& um){
    for(unsigned int i=0; i<vect_progr.size(); i++) vect_progr[i]=new Programmation(*um.vect_progr[i]);
}

Agenda& Agenda::operator=(const Agenda& um){
    if (this==&um) return *this;
    this->~Agenda();
    for(unsigned int i=0; i<um.vect_progr.size(); i++) addItem(new Programmation(*um.vect_progr[i]));
    return *this;
}*/
