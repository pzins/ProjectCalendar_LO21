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

    const QString getTitre() const {return titre;}
    const QDate getDispo() const {return dispo;}
    const QDate getEcheance() const {return echeance;}
    const QString& getDescription() const {return description;}


    /**
     * @brief info : renvoie une QString contenant les informations de la tache
     * @return
     */
    virtual const QString info() const;

    /**
     * @brief exportXml : exportation de la tache en XML
     * @param stream
     */
    virtual void exportXml(QXmlStreamWriter& stream) const=0;

    /**
     * @brief isComposite : test si une tache est composite
     * @return
     */
    virtual bool isComposite() const =0;

    /**
     * @brief operator == : entre deux taches
     * vrai si elle ont les meme titres
     * @param t
     * @return
     */
    bool operator==(const Tache& t);
};
#endif // TACHE_H
