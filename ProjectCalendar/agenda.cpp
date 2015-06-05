#include "agenda.h"
#include "jourscene.h"
#include "programmation.h"
#include "programmationrdv.h"

Agenda* Agenda::instance = 0;

Agenda::Agenda(){}


void Agenda::ajouterScene(qreal h, qreal w, QObject *parent)
{
    JourScene* js = new JourScene("Lundi",QDate(1994,3,20),0,0,w-2,h-2,840,parent);
    ajouterObservateur(js);
    scenes.push_back(js);
}


Agenda::~Agenda(){
    //for(unsigned int i=0; i<vect_progr.size(); i++) delete vect_progr[i];
   /* for(Agenda::Iterator it = vect_progr.begin(); it != vect_progr.end(); ++it)
        delete *it;*/
}

void Agenda::notifier(const QString& s1, const QString& s2)
{
    for(Observable::Iterator it = getObs().begin(); it != getObs().end(); ++it)
        (*it).update();
}



void Agenda::ajouterProgrammation(const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                  const Duree& duree, const QColor& contour, const QColor& fond)
{
    Programmation* p = new ProgrammationEvenement1J(date, debut, titre, desc, duree);
    try
    {
        for(std::set<Programmation*, ProgComp>::iterator it = set_prog.begin(); it != set_prog.end(); ++it)
        {
            if(date == (*it)->getDate())
            {
                std::cout << ")))" << std::endl;
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > debut)
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
        }
        if(set_prog.insert(p).second == false)
        {
            delete p;
            throw CalendarException("Erreur, Agenda, cette programmation existe deja");
        }
    JourScene* j = scenes.at(0);
    j->ajouterProgrammation(titre, debut, duree, p);
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
}


void Agenda::enleverProgrammation(Programmation* prog)
{
    if(prog)
    {


    }
    if(set_prog.erase(prog) == 0)
    throw CalendarException("Erreur, Agenda, cet Programmation n'existe pas");
}
