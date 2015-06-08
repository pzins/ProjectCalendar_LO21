#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include <vector>
#include <set>
#include <iostream>
#include "precedence.h"
#include "observable.h"
#include "xmlexporter.h"

/**
 * @class MyComp
 * @brief Comparateur pour le set de PrecedenceManager contenant des précédences
 */
class MyComp
{
public:
    bool operator()(Precedence* a, Precedence* b)
    {
        return !(*a == *b);
    }
};

/**
 * @class PrecedenceManager
 * @brief Classe permettant de gérer les précédences entre les taches
 *
 */
class PrecedenceManager : public Observable, public Observateur, public XmlExporter
{
private:
    std::set<Precedence*, MyComp> set_precedence;

    PrecedenceManager(){};
    virtual ~PrecedenceManager();
    PrecedenceManager(const PrecedenceManager& p);
    PrecedenceManager& operator=(const PrecedenceManager& p);

    static PrecedenceManager* instance;

public:
    std::set<Precedence*, MyComp> getVectPrecedence() const {return set_precedence;}

    static PrecedenceManager& getInstance(){
        if(!instance) instance = new PrecedenceManager();
        return *instance;
    }

    static void libererInstance(){
        delete instance;
    }

    /**
     * @brief ajouterPrecedence : ajout de précédence
     * @param pred_ tache antérieure
     * @param succ_ tache postérieure
     * @param projet_ projet concerné
     */
    void ajouterPrecedence(Tache& pred_, Tache& succ_, Projet& projet_);

    /**
     * @brief retirerPrecedence : suppression de précédences
     * @param p précédence
     */
    void retirerPrecedence(Precedence& p);

    /**
     * @brief containsInverse : vérifie si l'inverse d'une précédence n'est pas déjà présente
     * pour éviter les incohérences (A avant B et B avant A)
     * @param p précédence
     * @return
     */
    bool containsInverse(const Precedence& p) const;



    void update(const QString& s1="", const QString& s2="");
    void notifier(const QString& s1="", const QString& s2="");

    /**
     * @brief findPrecedence : renvoie toutes les précédences concernant une taches
     * @param pro projet
     * @param t tache
     * @return
     */
    std::vector<Precedence*> findPrecedence(Projet* pro, Tache* t);

    void save(const QString& f, bool contraintes=false);
    void load(const QString& f);


    /**
     * @class Iterator
     * @brief Iterator de PrecedenceManager sur les précédences
     */
    class Iterator
    {
    private:
        std::set<Precedence*,MyComp>::iterator courant;
    public:
        Iterator(std::set<Precedence*,MyComp>::iterator deb) : courant(deb){}
        Precedence& operator*() const {return **courant;}
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

    Iterator begin(){return Iterator(set_precedence.begin());}
    Iterator end(){return Iterator(set_precedence.end());}

    /**
     * @class ConstIterator
     * @brief ConstIterator de PrecedenceManager sur les précédences
     */
    class ConstIterator
    {
    private:
        std::set<Precedence*,MyComp>::const_iterator courant;
    public:
        ConstIterator(std::set<Precedence*,MyComp>::const_iterator deb) : courant(deb){}
        const Precedence& operator*() const {return **courant;}
        ConstIterator& operator++(){++courant; return *this;}
        ConstIterator operator++(int i){
            ConstIterator old = *this;
            ++courant;
            return old;
        }
        bool operator==(ConstIterator it) const{
            return courant == it.courant;
        }
        bool operator!=(ConstIterator it) const{
            return courant != it.courant;
        }
    };

    ConstIterator begin() const {return ConstIterator(set_precedence.begin());}
    ConstIterator end() const {return ConstIterator(set_precedence.end());}
};


#endif // PRECEDENCEMANAGER_H
