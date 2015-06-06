#include "dialogprogtache.h"
#include "ui_dialogprogtache.h"
#include "agenda.h"
#include "precedence.h"
#include "programmationtacheunitaire.h"
#include "programmation.h"

DialogProgTache* DialogProgTache::instance = 0;


DialogProgTache& DialogProgTache::getInstance(TacheUnitaire* tache, Projet* projet, QWidget* parent)
{
    if(instance)
    {
        instance->setTache(tache);
        instance->setProjet(projet);
        return *instance;
    }
    else
    {
        instance = new DialogProgTache(tache, projet, parent);
        return *instance;
    }
}

void DialogProgTache::libererInstance()
{
    delete instance;
    instance = 0;
}

DialogProgTache::DialogProgTache(TacheUnitaire* tache_, Projet* projet_, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogProgTache),
    projet(projet_), tache(tache_)

{
    ui->setupUi(this);
}

DialogProgTache::~DialogProgTache()
{
    delete ui;
}

void DialogProgTache::accept()
{
    std::cout << "TAche que lon prog : " <<tache->getTitre().toStdString() << std::endl;
    Agenda* ag = &Agenda::getInstance();
    try
    {
        verification();
        std::cout << tache->getDuree().toString().toStdString() << std::endl;
        ag->ajouterProgrammation(2, ui->date->date(), tache->getTitre(), tache->getDescription(),ui->horaire->time(),
                                 tache->getDuree(),"", "", tache );
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }

    close();
}

void DialogProgTache::verification()
{
    if(tache->getDispo() > ui->date->date()) throw CalendarException("Tache pas encore disponible");
    if(tache->getEcheance() < ui->date->date()) throw CalendarException("Echéance dépassée");
    Agenda* ag = &Agenda::getInstance();
    std::vector<Precedence*> vec = PrecedenceManager::getInstance().findPrecedence(projet, tache);
    std::cout << "TAILLE " << vec.size() << std::endl;
    for(std::vector<Precedence*>::iterator ite = vec.begin(); ite != vec.end(); ++ite)
    {
        if(tache->getTitre() == (*ite)->getSucc().getTitre())//boucle sur ttes les précédence dt la tache succ et celle que l'on prog
        {
            std::cout << "--------------" << std::endl;
            std::cout << "SIZE  ="<< ag->getProgrammation().size() << std::endl;
            for(Agenda::Iterator it = ag->begin(); it != ag->end(); ++it)//boucle sur ttes les taches déjà prog
            {
                std::cout << "^^^^^^^^^^^^^^" << std::endl;
                std::cout << (*it).getDate().toString().toStdString() << std::endl;
                //std::cout << (*it).isTache() << std::endl;
            for( std::set<Programmation*, ProgComp>::iterator it = Agenda::getInstance().getProgrammation().begin(); it != Agenda::getInstance().getProgrammation().end(); ++it)
            {
                std::cout << "+-+-+-+-+-     " << ((*it)==0)  << std::endl;
                //verif que c'est bien une prog de tache
                if((*it)->isTache())
                {
                    std::cout << "***************101010" << std::endl;

                    //conv en prog de tache uni
                    ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(*it);
                    if(ptu->getDate() > ui->date->date() || //verif si la tu est prog plus tard
                      (ptu->getDate() == ui->date->date() && ptu->getDebut() > ui->horaire->time()))//verif même jour debut !=
                    {
                        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                        throw CalendarException("Incohérence avec les contraintes de Précédences");

                    }

                }
                std::cout << "XXXX" <<std::endl;
            }}

        }
    }
}
