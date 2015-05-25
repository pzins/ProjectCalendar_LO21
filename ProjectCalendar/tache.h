#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include <QDate>
#include <QTextStream>
#include <QStandardItem>
#include <QComboBox>

#include "calendarexception.h"
#include "precedencemanager.h"

class Tache
{
private:
    unsigned int id;
    QString titre;
    QString description;
    QDate dispo;
    QDate echeance;


public:
    Tache(unsigned int id_, const QString& titre_, const QString& description_, const QDate& dispo_,
         const QDate& echeance_): id(id_), titre(titre_), description(description_), dispo(dispo_),
         echeance(echeance_){}
    virtual ~Tache(){}

    unsigned int getId() const {return id;}
    void setId(unsigned int id_){id = id_;}

    QString getTitre() const {return titre;}
    void setTitre(const QString& titre_) {titre=titre_;}

    QDate getDispo() const {return dispo;}

    QDate getEcheance() const {return echeance;}

    const QString& getDescription() const {return description;}
    void setDescription(const QString& description_) {description = description_;}

    void setDispoEcheance(const QDate& dispo_, const QDate& echeance_) {
        if (echeance_<dispo_) throw CalendarException("erreur Tache : date echeance < date disponibilite");
        dispo=dispo_;
        echeance=echeance_;
    }
    virtual void afficher(QStandardItem* it)=0;
    virtual void afficherComposite(QComboBox& c)=0;


/*
    class SuccIterator
    {
    private:
        friend class Tache;
        std::vector<Precedence*>::iterator courant;
        SuccIterator(std::vector<Precedence*>::iterator deb) : courant(deb){}
    public:
        SuccIterator() : courant(0){}
        Precedence& operator*() const {return **courant;}
        SuccIterator& operator++(){
            while(t != &(*courant)->getPred()) ++courant;
            return *this;
        }
        SuccIterator operator++(int i){
            SuccIterator old = *this;
            while(t != &(*courant)->getPred()) ++courant;
            return old;
        }
        bool operator==(SuccIterator it) const{
            return courant == it.courant;
        }
        bool operator!=(SuccIterator it) const{
            return courant != it.courant;
        }
    };

    SuccIterator begin(){return SuccIterator(PrecedenceManager::getInstance().getVectPrecedence().begin());}
    SuccIterator end(){return SuccIterator(PrecedenceManager::getInstance().getVectPrecedence().end());}
*/
};

#endif // TACHE_H
