#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include <vector>
#include <set>

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

    PrecedenceManager(){}
    ~PrecedenceManager();
    PrecedenceManager(const PrecedenceManager& p);
    PrecedenceManager& operator=(const PrecedenceManager& p);

    static PrecedenceManager* instance;

public:
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


    void update(const QString& s1="", const QString& s2="");
    void notifier(const QString& s1="", const QString& s2="") const;

    /**
     * @brief findPrecedence : renvoie toutes les précédences concernant une taches
     * @param pro projet
     * @param t tache
     * @return
     */
    std::vector<Precedence*> findPrecedence(Projet* pro, Tache* t);

    void save(const QString& f, bool contraintes=false) const;
    void load(const QString& f);


    /**
     * @class Iterator
     * @brief Iterator de PrecedenceManager sur les précédences
     */
    class Iterator : public std::set<Precedence*,MyComp>::iterator
    {
    public:
        Iterator(std::set<Precedence*,MyComp>::iterator deb) : std::set<Precedence*,MyComp>::iterator(deb){}
        Precedence& operator*() const {return *std::set<Precedence*,MyComp>::iterator::operator *();}
    };

    Iterator begin(){return Iterator(set_precedence.begin());}
    Iterator end(){return Iterator(set_precedence.end());}

    /**
     * @class ConstIterator
     * @brief ConstIterator de PrecedenceManager sur les précédences
     */
    class ConstIterator : public std::set<Precedence*,MyComp>::const_iterator
    {
    public:
        ConstIterator(std::set<Precedence*,MyComp>::const_iterator deb) :
            std::set<Precedence*,MyComp>::const_iterator(deb){}
        const Precedence& operator*() const {return *std::set<Precedence*,MyComp>::const_iterator::operator *();}
    };

    ConstIterator begin() const {return ConstIterator(set_precedence.begin());}
    ConstIterator end() const {return ConstIterator(set_precedence.end());}
};


#endif // PRECEDENCEMANAGER_H
