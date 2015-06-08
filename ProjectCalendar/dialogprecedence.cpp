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

        for(PrecedenceManager::Iterator it = pm->begin(); it != pm->end(); ++it)
        {
            if((*it).getSucc().getTitre() == ui->anterieure->currentText() && (*it).getPred().getTitre() == item_tache->data(0).toString())
            {
                throw CalendarException("Précédente incohérente car inverse présente");
            }
        }
        QStandardItem* it = item_tache;
        while(it->parent()) it = it->parent();
        Projet* p = ProjetManager::getInstance().getProjet(it->data(0).toString());
        Tache* ant = p->getTache(ui->anterieure->currentText());
        Tache* post = p->getTache(item_tache->data(0).toString());
        std::vector<QString> vec;
        if(ant->isComposite() || post->isComposite())
        {
            vec = ProjetManager::getInstance().getTacheFilles(ant->getTitre(), p->getTitre());
            for(std::vector<QString>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if(*it != ant->getTitre())
                {
                    Tache* ante = p->getTache(*it);
                    testDejaProg(ante, post);
                }
            }
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
        //verif pas dejà prog

        pm->ajouterPrecedence(*ant, *post, *p);

    }
    catch(CalendarException e)
    {
        QMessageBox::critical(this, "Erreur", e.getInfo());
    }
    close();
}

void DialogPrecedence::testDejaProg(Tache* ant, Tache* post)
{
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
