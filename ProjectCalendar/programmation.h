#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "duree.h"
#include <QTime>
#include <QXmlStreamReader>

/*
 * 5 types de Programmations
 * 0 : Programmation traditionelle 1 jour : P1J
 * 1 : Programmation rendez-vous            PRDV
 * 2 : Programmation tache unitaire         PTU
 * 3 : Programmation partie de tache        PPT
 * 4 : Programmation plusieurs jours        PPJ
 * */


/**
 * @class Programmation
 * @brief Classe abstraite représentant une programmation dans un agenda
 */
class Programmation {
    QDate date;
    QTime debut;

public:
    /**
     * @brief Programmation
     * @param date_ date de début
     * @param debut_ horaire de début
     */
    Programmation(const QDate& date_, const QTime& debut_): date(date_), debut(debut_){}

    /**
     * @brief ~Programmation : destructeur virtuel
     */
    virtual ~Programmation(){}

    QDate getDate() const {return date;}
    QTime getDebut() const {return debut;}

    /**
     * @brief toString : renvoie une QString contenant les informations de la programmation
     * @return
     */
    virtual const QString toString() const;

    virtual const Duree& getDuree() const =0;
    virtual const QString& getTitre() const =0;
    virtual const QString& getDescription() const =0;

    /**
     * @brief exportXml : permet l'export d'un programmation en xml
     * @param stream
     */
    virtual void exportXml(QXmlStreamWriter& stream) const =0;

    /**
     * @brief type : renvoie le type de la programmation
     * 0 : Programmation évènement 1 jour
     * 1 : Programmation rendez-vous
     * 2 : Programmation Tache Unitaire
     * 3 : Programmation Partie de tâche
     * 4 : Programmation évènement plusieurs jours
     */
    virtual const int type() const =0;
};


#endif // PROGRAMMATION_H
