#include "agenda.h"

Agenda* Agenda::instance = 0;

Agenda::Agenda(){}

Agenda::~Agenda(){
    //for(unsigned int i=0; i<vect_progr.size(); i++) delete vect_progr[i];
   /* for(Agenda::Iterator it = vect_progr.begin(); it != vect_progr.end(); ++it)
        delete *it;*/
}

/*
Agenda& Agenda::operator<<(Programmation& prog)
{
    for(std::vector<Programmation*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == &prog)
            throw CalendarException("Erreur, Agenda, cette programmation existe deja");
    prog.push_back(evt.clone());
    return *this;
}


Agenda& Agenda::operator>>(Programmation *evt)
{
    for(std::vector<Programmation*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == evt){
            delete evt;
            events.erase(it);
            return *this;
        }
    throw CalendarException("Erreur, Agenda, cet Programmation n'existe pas");
}*/
