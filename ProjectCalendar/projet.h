#ifndef PROJET_H
#define PROJET_H
#include "tache.h"
#include "tacheunitaire.h"
#include "tachecomposite.h"
#include <QString>
#include <stdexcept>

class Projet
{
    friend class ProjetManager;
private:
    unsigned int id;
    QString titre;
    QDate dispo;
    QDate echeance;
    unsigned int nb_tache;
    std::map<QString, Tache*> map_tache;
    std::map<QString, TacheComposite*> map_tache_compo;
    std::map<QString, TacheUnitaire*> map_tache_uni;


public:
    Projet(unsigned int id_, const QString& titre_, const QDate& dispo_, const QDate& echeance_) :
        id(id_), titre(titre_), dispo(dispo_), echeance(echeance_), nb_tache(0){}

    unsigned int getId() const {return id;}
    void setId(unsigned int id_){id = id_;}
    const QString& getTitre() const {return titre;}
    const QDate& getDispo() const {return dispo;}
    const QDate& getEcheance() const {return echeance;}

    void ajouterTacheUnitaire(const QString& titre, const QString& description,
                              const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive=false);
    void ajouterTacheComposite(const QString& titre, const QString& description,
                               const QDate& dispo, const QDate& echeance);

    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance)
    {
        if(titre == "") throw CalendarException("Veuillez entrer un titre");
        if(map_tache_compo.find(titre) != map_tache_compo.end()) throw CalendarException("Titre déjà attribué");
        if(map_tache_uni.find(titre) != map_tache_uni.end()) throw CalendarException("Titre déjà attribué");
        if(description == "") throw CalendarException("Veuillez entrer une description");

        if(echeance > this->echeance) throw CalendarException("Echéance et échéance du projet sont incohérentes");
        if(dispo < this->dispo) throw CalendarException("Disponibilité et disponibilité du projet sont incohérentes");
        if(dispo > echeance) throw CalendarException("Disponibilité et échéance sont incohérentes");
    }

    void retirerTache(QString& titre);

    const std::map<QString, Tache*>& getMapTache() const {return map_tache;}

    std::map<QString, TacheComposite*>& getMapTacheComposite() {return map_tache_compo;}
    std::map<QString, TacheUnitaire*>& getMapTacheUnitaire() {return map_tache_uni;}

    TacheComposite* getTacheComposite(const QString& titre)
    {
        try
        {
            return map_tache_compo.at(titre);
        }
        catch(out_of_range)
        {
            return 0;
        }
    }

   ~Projet();

    void save(const QString &titre);
    void load(const QString& f);




    class Iterator
    {
    private:
        friend class Projet;
        std::map<QString, Tache*>::iterator courant;
        Iterator(std::map<QString, Tache*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0){}
        Tache& operator*() const {return *(courant->second);}
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
    Iterator begin(){return Iterator(map_tache.begin());}
    Iterator end(){return Iterator(map_tache.end());}

    class Iterator_uni
    {
    private:
        friend class Projet;
        std::map<QString, TacheUnitaire*>::iterator courant;
        Iterator_uni(std::map<QString, TacheUnitaire*>::iterator deb) : courant(deb){}
    public:
        Iterator_uni() : courant(0){}
        TacheUnitaire& operator*() const {return *(courant->second);}
        Iterator_uni& operator++(){++courant; return *this;}
        Iterator_uni operator++(int i){
            Iterator_uni old = *this;
            ++courant;
            return old;
        }
        bool operator==(Iterator_uni it) const{
            return courant == it.courant;
        }
        bool operator!=(Iterator_uni it) const{
            return courant != it.courant;
        }
    };
    Iterator_uni begin(int i){return Iterator_uni(map_tache_uni.begin());}
    Iterator_uni end(int i){return Iterator_uni(map_tache_uni.end());}

    class Iterator_compo
    {
    private:
        friend class Projet;
        std::map<QString, TacheComposite*>::iterator courant;
        Iterator_compo(std::map<QString, TacheComposite*>::iterator deb) : courant(deb){}
    public:
        Iterator_compo() : courant(0){}
        TacheComposite& operator*() const {return *(courant->second);}
        Iterator_compo& operator++(){++courant; return *this;}
        Iterator_compo operator++(int i){
            Iterator_compo old = *this;
            ++courant;
            return old;
        }
        bool operator==(Iterator_compo it) const{
            return courant == it.courant;
        }
        bool operator!=(Iterator_compo it) const{
            return courant != it.courant;
        }
    };
    Iterator_compo begin(char a){return Iterator_compo(map_tache_compo.begin());}
    Iterator_compo end(char a){return Iterator_compo(map_tache_compo.end());}
};


#endif // PROJET_H
