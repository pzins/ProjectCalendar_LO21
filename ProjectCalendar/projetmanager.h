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
    void ajouterProjet(const QString& titre, const QString& description_, const QDate& dispo,
                       const QDate& echeance);

    void retirerProjet(QString &titre);

    const std::map<QString, Projet*>& getMapProjet() const {return map_projet;}
    Projet* getProjet(const QString &titre);

    QStandardItemModel& getModel(){return model;}

    void save(const QString& f);
    void saveModel(const QString& f);
    void rec_fct(const QStandardItem &item, QXmlStreamWriter& str, QString pere);
    QStandardItem* getChild(QStandardItem *item, QString &titre);

    void load(const QString& f);
    void loadModel(const QString& f);

    void ajoutItemModel(const QString& titre,const QModelIndex& idx)
    {
        QStandardItem* item = new QStandardItem(titre);
        if(idx == model.invisibleRootItem()->index())
        {
            model.invisibleRootItem()->appendRow(item);
        }
        else
        {
            QStandardItem* i = model.itemFromIndex(idx);
            i->appendRow(item);
        }

    }

    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance)
    {
        if(titre == "") throw CalendarException("Veuillez entrer un titre");
        if(description == "") throw CalendarException("Veuillez entrer une description");
        if(map_projet.find(titre) != map_projet.end()) throw CalendarException("Nom déjà attribué");
        if(dispo > echeance) throw CalendarException("Disponibilité et echeance incohérentes");
    }

    void update();

    void findChildren(std::vector<QString>& vec, QModelIndex& selected);

    void supprimerItem(QModelIndexList& sel);

    void rec(QStringList &str, int nb, int current, QStandardItem *it);


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
