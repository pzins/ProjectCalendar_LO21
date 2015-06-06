#include "agenda.h"
#include "jourscene.h"
#include "programmation.h"
#include "programmationrdv.h"
#include "programmationtacheunitaire.h"

Agenda* Agenda::instance = 0;



void Agenda::ajouterScene(const QString& jour, const QDate& date, qreal h, qreal w, QObject *parent)
{
    JourScene* js = new JourScene(jour,date,0,0,w-2,h-2,840,parent);
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
    {
        (*it).update();
    }
}

void Agenda::ajouterProgrammationPlsJour(const QDate& date, const QString titre, const QString& desc,
                                         const QTime& debut, const QDate& date_fin, const QTime& fin,
                                         const QColor& contour, const QColor& fond)
{
    ProgrammationEvenementplsJ* p = new ProgrammationEvenementplsJ(date, debut, titre, desc, date_fin, fin);
    try
    {
        verifProgrammation(p);
        ajouterProgrammationPlsJour(p);
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
}

void Agenda::ajouterProgrammationPlsJour(ProgrammationEvenementplsJ* p)
{
    int nb_jour = p->getDate().daysTo(p->getDateFin())+1;
    Duree d1(QTime(8,0).secsTo(p->getFin()) / 60);
    Duree d2(p->getDebut().secsTo(QTime(22,0)) / 60);


    for(int i = 0; i < nb_jour; ++i)
    {

        JourScene* j = scenes.at(p->getDate().dayOfWeek()-1+i);
        if(i==0)
            j->ajouterProgrammation(p->getTitre(), p->getDebut(), d2, p);
        else if(i == nb_jour-1)
            j->ajouterProgrammation(p->getTitre(), QTime(8,0), d1, p);
        else
            j->ajouterProgrammation(p->getTitre(), QTime(8,0), Duree(14,0), p);
    }
}

void Agenda::verifProgrammation(Programmation* p)
{
    for(std::set<Programmation*, ProgComp>::iterator it = set_prog.begin(); it != set_prog.end(); ++it)
    {
       /* if(p->isTache())
        {
            ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(p);
            if(ptu->getDate() == (*it)->getDate() && (*it)->getDebut() < ptu->getTache()->getDebut())
            {
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > ptu->getTache()->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
        }*/
      if(p->isEvtPlsJ())
        {
            ProgrammationEvenementplsJ* tmp = dynamic_cast<ProgrammationEvenementplsJ*>(p);
            if(tmp->getDate() == (*it)->getDate())
            {
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > tmp->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
            else if (tmp->getDateFin() == (*it)->getDate())
            {
                if(tmp->getFin() > (*it)->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
            else if(tmp->getDate() < (*it)->getDate() && tmp->getDateFin() > (*it)->getDate())
            {
                throw CalendarException("Erreur, Agenda, chevauchement de programmation");
            }
        }
        else
        {
            if(p->getDate() == (*it)->getDate() && (*it)->getDebut() < p->getDebut())
            {
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > p->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
        }
    }
    if(set_prog.insert(p).second == false)
    {
        delete p;
        throw CalendarException("Erreur, Agenda, cette programmation existe deja");
    }
}


void Agenda::ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                  const Duree& duree, const QString& lieu, const QString& pers, const TacheUnitaire* tache,
                                  const QColor& contour, const QColor& fond)
{
    Programmation* p;
    if(type == 0)
        p = new ProgrammationEvenement1J(date, debut, titre, desc, duree);
    else if(type == 1)
        p = new ProgrammationRdv(date, debut, titre, desc, duree, lieu, pers);
    else if(type == 2)
    {
        std::cout << "()()()()()((   " << duree.toString().toStdString() << std::endl;
        p = new ProgrammationTacheUnitaire(date, debut, *tache);
    }
    try
    {
        verifProgrammation(p);
        std::cout << "$$$$$$    avant ajout " << p->getDate().toString().toStdString() << std::endl;
        JourScene* j = scenes.at(date.dayOfWeek()-1);
        std::cout << ";;;;;   DUREE " << p->getDuree().toString().toStdString() << std::endl;
        std::cout << ";;;;;   DEBUT " << p->getDebut().toString().toStdString() << std::endl;
        j->ajouterProgrammation(titre, debut, duree, p);
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
}


void Agenda::enleverProgrammation(Programmation* prog)
{
    if(set_prog.erase(prog) == 0)
        throw CalendarException("Erreur, Agenda, cet Programmation n'existe pas");
}
