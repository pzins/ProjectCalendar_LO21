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
    ui->date->setDate(QDate::currentDate());
}

DialogProgTache::~DialogProgTache()
{
    delete ui;
}

void DialogProgTache::accept()
{
    Agenda* ag = &Agenda::getInstance();
    try
    {
        verification();
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
    for(std::vector<Precedence*>::iterator ite = vec.begin(); ite != vec.end(); ++ite)
    {
        if(tache->getTitre() == (*ite)->getSucc().getTitre())//boucle sur ttes les précédence dt la tache succ et celle que l'on prog
        {
            for(Agenda::Iterator it = ag->begin(); it != ag->end(); ++it)//boucle sur ttes les taches déjà prog
            {
                //verif que c'est bien une prog de tache
                if((*it).isTache())
                {
                    //conv en prog de tache uni
                    ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(&(*it));
                    if(ptu->getDate() > ui->date->date() || //verif si la tu est prog plus tard
                      (ptu->getDate() == ui->date->date() && ptu->getDebut() > ui->horaire->time()))//verif même jour debut !=
                    {
                        throw CalendarException("Incohérence avec les contraintes de Précédences");
                    }
                }
            }
        }
    }
}
