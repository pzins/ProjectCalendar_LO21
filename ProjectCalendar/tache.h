#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include <QDate>
#include <QTextStream>
#include "calendarexception.h"

class Tache
{
private:
    QString id;
    QString titre;
    QString description;
    QDate dispo;
    QDate echeance;


public:
    Tache(const QString& id_, const QString& titre_, const QString& description_, const QDate& dispo_,
         const QDate& echeance_): id(id_), titre(titre_), description(description_), dispo(dispo_),
         echeance(echeance_){}
    virtual ~Tache(){}

    QString getId() const {return id;}
    void setId(const QString& id_){id = id_;}

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

    virtual void afficher() const =0;

};

#endif // TACHE_H
