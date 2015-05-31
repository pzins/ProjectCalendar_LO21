#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include "projet.h"
#include "observateur.h"

#include <QString>
#include <QStandardItemModel>
#include <QTreeView>


class ProjetManager : public Observateur, public QStandardItemModel
{
private:
    std::map<QString, Projet*> map_projet;
    ProjetManager(){}
    ~ProjetManager(){}
    ProjetManager(const ProjetManager& p){}
    ProjetManager& operator=(const ProjetManager& p){}

    static ProjetManager* instance;

    QStandardItemModel model;

public:

    static ProjetManager& getInstance(){
        if(!instance) instance = new ProjetManager();
        return *instance;
    }

    static void libererInstance(){
        delete instance;
    }

    const std::map<QString, Projet*>& getMapProjet() const {return map_projet;}
    QStandardItemModel& getModel(){return model;}



    void ajouterProjet(const QString& titre, const QString& description_, const QDate& dispo,
                       const QDate& echeance);

    void retirerProjet(QString &titre);

    Projet* getProjet(const QString &titre);


    void save(const QString& f);//sauvegarde les projets
    void saveModel(const QString& f);//sauvegarde le modele
    void save_recursive(const QStandardItem &item, QXmlStreamWriter& str, QString pere);//aide saveModel




    void load(const QString& f);//charge les projets
    void loadModel(const QString& f);//charge le modele
    void appendChild(QStandardItem *item, const QString& pere, const QString& titre);//aide loadModel

    //recupère des infos sur des les éléments du model, à partir d'un index
    QString getInfo(QModelIndex idx);


    //renvoie un vector contenant toutes les taches filles d'une tache à partir du nom de la tache de base et du projet
    std::vector<QString> getTacheFilles(const QString& tache, const QString& projet);
    //fct recursive qui aide getTacheFille, en appelant finditem
    void findItem(QStandardItem* projet, const QString& item, std::vector<QString> &vec);

    //ajoute un élément au modele à partir de l'index
    void ajoutItemModel(const QString& titre,const QModelIndex& idx);


    //fait les vérification lors de l'ajout d'un projet
    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance);


    void update();//à enlever surement

    //ajout ds vec les nom de ttes les taches filles de la tache item
    void findChildren(std::vector<QString> &vec, QStandardItem* item);

    //supprime des taches ou projet
    void supprimerItem(QModelIndex &sel);


    class Iterator
    {
    private:
        friend class ProjetManager;
        std::map<QString, Projet*>::iterator courant;
        Iterator(std::map<QString, Projet*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0){}
        Projet& operator*() const {return *courant->second;}
        Iterator& operator++(){++courant; return *this;}
        Iterator operator++(int i){
            Iterator old = *this;
            ++courant;
            return old;
        }
        bool operator==(Iterator it) const{
            return courant == it.courant;
        }
        bool operator!=(Iterator it) const{
            return courant != it.courant;
        }
    };

    Iterator begin(){return Iterator(map_projet.begin());}
    Iterator end(){return Iterator(map_projet.end());}

};

#endif // PROJETMANAGER_H
