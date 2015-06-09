#include "dialogprecedence.h"
#include "ui_dialogprecedence.h"
#include "agenda.h"
#include <QMessageBox>


DialogPrecedence::DialogPrecedence(QStandardItem* it, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrecedence),
    item_tache(it)
{
    ui->setupUi(this);
    chargerAnterieure();
}

DialogPrecedence::~DialogPrecedence()
{
    delete ui;
}

void DialogPrecedence::chargerAnterieure()
{
    if(item_tache->parent())
    {
        QStandardItem* parent = item_tache->parent();
        //parcourt les taches possibles
        for(int i = 0; i < parent->rowCount(); ++i)
        {
            QString str = parent->child(i,0)->data(0).toString();
            if(str != item_tache->data(0).toString())
                ui->anterieure->addItem(str);
        }
    }
}

void DialogPrecedence::accept()
{
    PrecedenceManager* pm = &PrecedenceManager::getInstance();
    try
    {
        QStandardItem* it = item_tache;
        while(it->parent()) it = it->parent();
        Projet* p = ProjetManager::getInstance().getProjet(it->data(0).toString());
        Tache* ant = p->getTache(ui->anterieure->currentText());
        Tache* post = p->getTache(item_tache->data(0).toString());
        std::vector<QString> vec;
        //si la tache anterieure ou posterieure est composite
        if(ant->isComposite() || post->isComposite())
        {
            vec = ProjetManager::getInstance().getTacheFilles(ant->getTitre(), p->getTitre());
            //on ajoute la précédence à toutes les tache filles
            for(std::vector<QString>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if(*it != ant->getTitre())
                {
                    Tache* ante = p->getTache(*it);
                    testDejaProg(ante, post);
                }
            }
            //on ajoute la précédence à toutes les tache filles
            vec = ProjetManager::getInstance().getTacheFilles(post->getTitre(), p->getTitre());
            for(std::vector<QString>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if(*it != post->getTitre())
                {
                    Tache* poste = p->getTache(*it);
                    testDejaProg(ant, poste);
                }
            }
        }
        testDejaProg(ant, post);
        //on a d'abord vérifiées si il n'y a pas d'erreur et maintenant on ajoute vraiment les précédences dans le
        //PrecedenceManager à partir du vecteur vec
        //pour éviter l'ajout de seulement une partie des précédences (tout ou rien)
        if(ant->isComposite())
        {
            vec = ProjetManager::getInstance().getTacheFilles(ant->getTitre(), p->getTitre());
            for(std::vector<QString>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if(*it != ant->getTitre())
                {
                    Tache* ante = p->getTache(*it);
                    pm->ajouterPrecedence(*ante,*post, *p);
                }
            }
        }
        if(post->isComposite())
        {
            vec = ProjetManager::getInstance().getTacheFilles(post->getTitre(), p->getTitre());
            for(std::vector<QString>::iterator it = vec.begin()+1; it != vec.end(); ++it)
            {
                if(*it != post->getTitre())
                {
                    Tache* poste = p->getTache(*it);
                    pm->ajouterPrecedence(*ant,*poste, *p);
                }
            }
        }
        pm->ajouterPrecedence(*ant, *post, *p);
        close();
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }
}

void DialogPrecedence::testDejaProg(Tache* ant, Tache* post)
{
    //vérification si tache postérieure ou antérieure est déjà programmée => erreur
    if(!ant->isComposite())
    {
        TacheUnitaire* tu = dynamic_cast<TacheUnitaire*>(ant);
        if(tu->isProgrammed())
                    throw CalendarException("Impossible tâche déjà programmée : " + ant->getTitre() + " ou " +
                                            post->getTitre());
    }
    if(!post->isComposite())
    {
        TacheUnitaire* tu = dynamic_cast<TacheUnitaire*>(post);
        if(tu->isProgrammed())
            throw CalendarException("Impossible tâche déjà programmée : " + ant->getTitre() + " ou " +
                                    post->getTitre());
    }
}
