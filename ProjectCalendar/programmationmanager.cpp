#include "programmationmanager.h"


ProgrammationManager::ProgrammationManager(){}

void ProgrammationManager::addItem(Programmation* t){
    vect_progr.push_back(t);
}

Programmation* ProgrammationManager::trouverProgrammation(const Tache& t)const{
    for(unsigned int i=0; i<vect_progr.size(); i++)
        if (&t==&vect_progr[i]->getTache()) return vect_progr[i];
    return 0;
}

void ProgrammationManager::ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h){
    if (trouverProgrammation(t)) throw CalendarException("erreur, ProgrammationManager, Programmation deja existante");
    Programmation* newt=new Programmation(t,d,h);
    addItem(newt);
}


ProgrammationManager::~ProgrammationManager(){
    for(unsigned int i=0; i<vect_progr.size(); i++) delete vect_progr[i];
}

ProgrammationManager::ProgrammationManager(const ProgrammationManager& um){
    for(unsigned int i=0; i<vect_progr.size(); i++) vect_progr[i]=new Programmation(*um.vect_progr[i]);
}

ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& um){
    if (this==&um) return *this;
    this->~ProgrammationManager();
    for(unsigned int i=0; i<um.vect_progr.size(); i++) addItem(new Programmation(*um.vect_progr[i]));
    return *this;
}
