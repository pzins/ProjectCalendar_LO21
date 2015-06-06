#ifndef AGENDA_H
#define AGENDA_H
#include <vector>
#include <iostream>
#include <set>
#include "tache.h"
#include "programmationevenement1j.h"
#include "jourscene.h"
#include "observable.h"

class ProgComp
{
public:
    bool operator()(Programmation* a, Programmation* b)
    {
        return (a->getDate() < b->getDate())||
                (a->getDate() == b->getDate() && a->getDebut() < b->getDebut());
    }
};

class Agenda : public Observable
{
private:
    std::set<Programmation*, ProgComp> set_prog;
    std::vector<JourScene*> scenes;

    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;

    Agenda(QDate auj_);
    ~Agenda();
    Agenda(const Agenda& a);
    Agenda& operator=(const Agenda& a);

    static Agenda* instance;
    QDate auj;


public:
    const QDate& getAuj() const {return auj;}
    void setAuj(QDate d){auj = d;}
    static Agenda& getInstance(){
        if(!instance) instance = new Agenda(QDate::currentDate());
        return *instance;
    }
    static void libererInstance(){delete instance;}

    void ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc, const QTime& debut,
    const Duree& duree,  const QString& lieu="", const QString& pers="", const QColor& contour=QColor("black"),
                              const QColor& fond=QColor("red"));

    void ajouterProgrammationPlsJour(const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                     const QDate& date_fin, const QTime& fin, const QColor& contour=QColor("black"),
                                     const QColor& fond=QColor("red"));

    void enleverProgrammation(Programmation* prog);

    void verifProgrammation(Programmation* p);

    void ajouterScene(const QString &jour, const QDate &date, qreal h, qreal w, QObject* parent = 0 );
    JourScene& getScene(int i) const {return *scenes.at(i);}
    std::set<Programmation*, ProgComp> getProgrammation() const {return set_prog;}

    virtual void notifier(const QString& s1="", const QString& s2="");














    class Iterator
    {
    private:
        friend class Agenda;
        std::set<Programmation*, ProgComp>::iterator courant;
        Iterator(std::set<Programmation*, ProgComp>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0) {}
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
