#include "agenda.h"
#include "jourscene.h"
#include "programmation.h"
#include "programmationrdv.h"
#include "programmationtacheunitaire.h"
#include "programmationpartietache.h"

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
        if(set_prog.insert(p).second == false)
        {
            delete p;
            throw CalendarException("Erreur, Agenda, une programmation existe à cette heure");
        }
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
    notifier();
}



void Agenda::verifProgrammation(Programmation* p)
{
    for(std::set<Programmation*, ProgComp>::iterator it = set_prog.begin(); it != set_prog.end(); ++it)
    {
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
            else if(p->getDate() == (*it)->getDate() && (*it)->getDebut() > p->getDebut())
            {
                QTime fin = p->getDebut().addSecs(p->getDuree().getDureeEnMinutes() * 60);
                if(fin > (*it)->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
        }
    }
}

void Agenda::ajouterProgrammationPartieTache(std::vector<QDate>& vec_date, std::vector<QString>& vec_titre,
                                             std::vector<QTime>& vec_debut, std::vector<Duree>& vec_duree,
                                             TacheUnitaire* t)
{
   std::vector<ProgrammationPartieTache*> vec;

   try
   {
       ProgrammationPartieTache* p;
       for(int i = 0; i < vec_date.size(); ++i)
       {
           p = new ProgrammationPartieTache(vec_date.at(i), vec_debut.at(i), *t, i+1,
                                                                      vec_titre.at(i), vec_duree.at(i));
           vec.push_back(p);
           verifProgrammation(p);
       }
       for(int i = 0; i < vec.size(); ++i)
       {
           if(set_prog.insert(vec.at(i)).second == false)
           {
               delete p;
               throw CalendarException("Erreur, Agenda, une programmation existe à cette heure");
           }
       }
   }
   catch(CalendarException e)
   {
       std::cout << e.getInfo().toStdString() << std::endl;

       /*for(int i = 0; i < vec.size(); ++i)
       {
           delete vec.at(i);
       }*/
   }

}


void Agenda::ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                  const Duree& duree, const QString& lieu, const QString& pers, TacheUnitaire* tache,
                                  const QColor& contour, const QColor& fond)
{
    Programmation* p;
    if(type == 0)
        p = new ProgrammationEvenement1J(date, debut, titre, desc, duree);
    else if(type == 1)
        p = new ProgrammationRdv(date, debut, titre, desc, duree, lieu, pers);
    else if(type == 2)
        p = new ProgrammationTacheUnitaire(date, debut, *tache);
    try
    {
        verifProgrammation(p);
        if(set_prog.insert(p).second == false)
        {
            delete p;
            throw CalendarException("Erreur, Agenda, une programmation existe à cette heure");
        }
        if(type == 2)
            tache->setIsProgrammed(true);
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
    notifier();
}

void Agenda::enleverProgrammation(Programmation* prog)
{
    if(prog->isTache())
    {
        ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(prog);
        ptu->getTache()->setIsProgrammed(false);
    }
    if(set_prog.erase(prog) == 0)
        throw CalendarException("Erreur, Agenda, cet Programmation n'existe pas");
    notifier();
}
