#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include "projet.h"
#include "observateur.h"
#include "xmlexporter.h"

#include <QStandardItemModel>
#include <QTreeView>


/**
 * @class ProjetManager
 * @brief Classe qui gère les projets
 */
class ProjetManager : public QStandardItemModel, public Observable, public XmlExporter
{
private:
    std::map<QString, Projet*> map_projet;
    ProjetManager(){}
    ~ProjetManager();
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

    /**
     * @brief getProjet : retourne un pointeur sur le projet à partir du nom
     * @param titre
     * @return
     */
    Projet* getProjet(const QString &titre);


    /**
     * @brief save : sauvegarde des projets
     * @param f
     * @param contraintes
     */
    void save(const QString& f, bool contraintes=false) const;
    /**
     * @brief saveModel : sauvegarde du model (structure des projets)
     * @param f
     */
    void saveModel(const QString& f);//sauvegarde le modele

    /**
     * @brief save_recursive : fonction récursie utilisée par saveModel
     * @param item
     * @param str
     * @param pere
     */
    void save_recursive(const QStandardItem &item, QXmlStreamWriter& str, QString pere);//aide saveModel

    /**
     * @brief load : chargement des projets
     * @param f
     */
    void load(const QString& f);

    /**
     * @brief loadModel : chargement du model (structure des projets)
     * @param f
     */
    void loadModel(const QString& f);//charge le modele
    /**
     * @brief appendChild : fonction récursive utilisée par lodamodel
     * @param item
     * @param pere
     * @param titre
     */
    void appendChild(QStandardItem *item, const QString& pere, const QString& titre);

    /**
     * @brief getInfo : récupère des informations sur les taches ou projets sélectionnés
     * @param idx index
     * @return
     */
    QString getInfo(QModelIndex idx);

    /**
     * @brief ajoutItemModel : ajoute un élément au model à partir de l'index
     * @param titre
     * @param idx index
     */
    void ajoutItemModel(const QString& titre,const QModelIndex& idx);


    /**
     * @brief verification : vérifications lors de l'ajout d'un nouveau projet
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     */
    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance);

    /** ==============  FONCTIONS OUTILS =====================**/

    /**
     * @brief getTacheFilles : renvoie un vector contenant toutes les taches filles
     *d'une tache à partir du nom de la tache de base et du projet
     *  @param tache
     * @param projet
     * @return
     */
    std::vector<QString> getTacheFilles(const QString& tache, const QString& projet);

    /**
     * @brief findItem : fonction qui aide getTacheFille, en appelant finditem
     * @param projet
     * @param item
     * @param vec
     */
    void findItem(QStandardItem* projet, const QString& item, std::vector<QString> &vec);


    /**
     * @brief findChildren : ajout dans vec de toutes les taches filles de la tache item
     * @param vec
     * @param item
     */
    void findChildren(std::vector<QString> &vec, QStandardItem* item);

    //supprime des taches ou projet
    /**
     * @brief supprimerItem : suppression de taches ou projet
     * @param sel
     */
    void supprimerItem(QModelIndex &sel);

    /**
     * @brief getProjetName
     * @param idx
     * @return nom d'un projet à partir d'un index
     */
    QString getProjetName(QModelIndex idx);
    /**
     * @brief getTacheName
     * @param idx
     * @return nom d'une tache à partir d'un index
     */
    QString getTacheName(QModelIndex idx);


    virtual void notifier(const QString& s1="", const QString& s2="") const;

    /**
     * @class Iterator
     * @brief Iterator de ProjetManager, parcourt les projets
     */
    class Iterator : public std::map<QString, Projet*>::iterator
    {
    public:
        Iterator(std::map<QString, Projet*>::iterator deb) : std::map<QString, Projet*>::iterator(deb){}
        Projet& operator*() const {return *std::map<QString, Projet*>::iterator::operator *().second;}
    };

    Iterator begin(){return Iterator(map_projet.begin());}
    Iterator end(){return Iterator(map_projet.end());}

    /**
     * @class ConstIterator
     * @brief ConstIterator de ProjetManager, parcourt les projets
     */
    class ConstIterator : public std::map<QString, Projet*>::const_iterator
    {
    public:
        ConstIterator(std::map<QString, Projet*>::const_iterator deb) : std::map<QString, Projet*>::const_iterator(deb){}
        const Projet& operator*() const {return *std::map<QString, Projet*>::const_iterator::operator *().second;}
    };

    ConstIterator begin() const {return ConstIterator(map_projet.begin());}
    ConstIterator end() const {return ConstIterator(map_projet.end());}

};

#endif // PROJETMANAGER_H
