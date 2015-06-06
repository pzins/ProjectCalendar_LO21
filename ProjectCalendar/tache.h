#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include <QDate>
#include <QTextStream>
#include <QStandardItem>
#include <QComboBox>
#include <QtXml>

#include "calendarexception.h"



class Tache
{
private:
    QString titre;
    QString description;
    QDate dispo;
    QDate echeance;

public:
    Tache(const QString& titre_, const QString& description_, const QDate& dispo_,
         const QDate& echeance_): titre(titre_), description(description_), dispo(dispo_),
         echeance(echeance_){}
    virtual ~Tache(){}

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


    virtual void exportXml(QXmlStreamWriter& stream)=0;
    virtual bool isComposite() const =0;
    virtual QString info() const=0;

    bool operator==(const Tache& t);

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
