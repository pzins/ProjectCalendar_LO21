#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include <vector>
#include <set>
#include <iostream>
#include "precedence.h"
#include "observable.h"
#include "xmlexporter.h"

class MyComp
{
public:
    bool operator()(Precedence* a, Precedence* b)
    {
        return !(*a == *b);
    }
};


class PrecedenceManager : public Observable, public Observateur, public XmlExporter
{
private:
    std::set<Precedence*, MyComp> set_precedence;

    PrecedenceManager(){}
    virtual ~PrecedenceManager();
    PrecedenceManager(const PrecedenceManager& p){}
    PrecedenceManager& operator=(const PrecedenceManager& p){}

    static PrecedenceManager* instance;

public:
    std::set<Precedence*, MyComp> getVectPrecedence() const {return set_precedence;}

    static PrecedenceManager& getInstance(){
        if(!instance) instance = new PrecedenceManager();
        return *instance;
    }

    static void liberer_instance(){
        delete instance;
    }

    void ajouterPrecedence(Tache& pred_, Tache& succ_, Projet& projet_);
    void retirerPrecedence(Precedence& p);
   // bool contains(const Precedence& p); //plus besoin car j'ai ajouté un comparator perso
    bool containsInverse(const Precedence& p) const;



    void update(const QString& s1="", const QString& s2="");
    void notifier(const QString& s1="", const QString& s2="");

    std::vector<Precedence*> findPrecedence(Projet* pro, Tache* t);

    void save(const QString& f, bool contraintes=false);
    void load(const QString& f);


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
