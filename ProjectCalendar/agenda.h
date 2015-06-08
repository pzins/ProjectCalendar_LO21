#ifndef AGENDA_H
#define AGENDA_H
#include <vector>
#include <iostream>
#include <set>
#include "tache.h"
#include "programmationevenement1j.h"
#include "programmationevenementplsj.h"
#include "programmationtacheunitaire.h"
#include "jourscene.h"
#include "observable.h"
#include "tacheunitaire.h"
#include "xmlexporter.h"



/**
 * @class ProgComp
 * @brief Comparateur pour le set de l'agenda contenant les programmations
 */
class ProgComp
{
public:

    /**
     * @brief operator ()
     * @param a première programmation
     * @param b seconde programmation
     * @return a < b
     */
    bool operator()(Programmation* a, Programmation* b)
    {
        return QDateTime(a->getDate(), a->getDebut()) < QDateTime(b->getDate(), b->getDebut());
    }
};




/**
 * @class Agenda
 * @brief Gère l'ensemble des programmations
 */
class Agenda : public Observable,  public XmlExporter
{
private:

    std::set<Programmation*, ProgComp> set_prog;
    std::vector<JourScene*> scenes;
    Agenda(){}
    Agenda(const Agenda& a);
    Agenda& operator=(const Agenda& a);
    ~Agenda();
    static Agenda* instance;

public:
    static Agenda& getInstance(){
        if(!instance) instance = new Agenda();
        return *instance;
    }
    static void libererInstance(){delete instance;}


    /**
     * @brief ajouterProgrammation : ajout d'une programmation dans l'agenda
     * @param type type de la programmation
     * @param date date de début
     * @param titre
     * @param desc description
     * @param debut
     * @param duree
     * @param lieu lieu : si rendez-vous
     * @param pers participants : si rendez-vous
     * @param tache tache correspondant à la programmation : si programmation de TacheUnitaire ou partie de Tache
     * @param projet tache correspondant à la tache : si programmation de TacheUnitaire ou de partie de tache
     * @param num_partie numéro de la prtie : si programmation de partie de tache
     * @param nom_partie nom de la partie : si programmation de partie de tache
     */
    void ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                              const Duree& duree,  const QString& lieu="", const QString& pers="",
                              TacheUnitaire* tache = 0, const QString &projet="", int num_partie=0,
                              const QString nom_partie="");


    /**
     * @brief ajouterProgrammationPlsJour : ajout d'une programmation sur plusieurs jours dans l'agenda
     * @param date date de début
     * @param titre
     * @param desc description
     * @param debut horaire de début
     * @param date_fin date de fin
     * @param fin horaire de fin
     */
    void ajouterProgrammationPlsJour(const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                     const QDate& date_fin, const QTime& fin);
    /**
     * @brief ajouterProgrammationPartieTache : ajout de programmations pour des parties de tâche
     * @param vec_date vecteur contenant les date de début
     * @param vec_titre vecteur contenant les titre des parties
     * @param vec_debut vecteur contenant les horaire de début des parties
     * @param vec_duree vecteur contenant les durées des parties
     * @param t tache unitaire correspondante
     * @param projet
     */
    void ajouterProgrammationPartieTache(std::vector<QDate>& vec_date, std::vector<QString>& vec_titre,
                                                 std::vector<QTime>& vec_debut, std::vector<Duree>& vec_duree,
                                         TacheUnitaire *t, const QString &projet);
    /**
     * @brief enleverProgrammation : suppression d'une programmation de l'agenda
     * @param prog programmation
     */
    void enleverProgrammation(Programmation* prog);

    /**
     * @brief verifProgrammation : vérification des contraintes d'une programmation
     * @param p programmation
     */
    void verifProgrammation(Programmation* p);

    /**
     * @brief ajouterScene : ajout d'une scene dans l'agenda
     * @param jour
     * @param date
     * @param h hauteur de la scene
     * @param w largeur de la scene
     * @param parent
     */
    void ajouterScene(const QString &jour, const QDate &date, qreal h, qreal w, QObject* parent = 0);


    JourScene& getScene(int i) const {return *scenes.at(i);}
    void removeAllScenes(){scenes.clear();}
    std::set<Programmation*, ProgComp> getProgrammation() const {return set_prog;}


    virtual void notifier(const QString& s1="", const QString& s2="");




    void save(const QString& f, bool contraintes=false);
    void load(const QString& f);



    /**
     * @class Iterator
     * @brief Iterator sur les programmations de l'agenda
     */
    class Iterator
    {
    private:
        std::set<Programmation*, ProgComp>::iterator courant;
    public:
        Iterator(std::set<Programmation*, ProgComp>::iterator deb) : courant(deb){}
        Programmation& operator*() const {return **courant;}
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

    Iterator begin(){return Iterator(set_prog.begin());}
    Iterator end(){return Iterator(set_prog.end());}

};

#endif // AGENDA_H
