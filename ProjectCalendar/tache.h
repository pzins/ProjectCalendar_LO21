#ifndef TACHE_H
#define TACHE_H
#include <QDate>
#include <QXmlStreamReader>

#include "calendarexception.h"
#include "affichable.h"

/**
 * @class Tache
 * @brief Classe abstraite représentant une Tache
 */
class Tache : public Affichable
{
private:
    QString titre;
    QString description;
    QDate dispo;
    QDate echeance;

public:
    /**
     * @brief Tache
     * @param titre_
     * @param description_
     * @param dispo_ date de disponibilité
     * @param echeance_ date d'échéance
     */
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

    virtual const QString info() const;

    virtual void exportXml(QXmlStreamWriter& stream) const=0;
    virtual bool isComposite() const =0;
    bool operator==(const Tache& t);
};
#endif // TACHE_H
