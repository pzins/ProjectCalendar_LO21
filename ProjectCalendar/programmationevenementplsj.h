#ifndef PROGRAMMATIONEVENEMENTPLSJ_H
#define PROGRAMMATIONEVENEMENTPLSJ_H
#include "programmationevenement.h"

/**
 * @class ProgrammationEvenementplsJ
 * @brief Classe représentant la programmation d'un évènement sur plusieurs jours
 */
class ProgrammationEvenementplsJ : public ProgrammationEvenement
{
private:
    QDate date_fin;
    QTime fin;
public:
    /**
     * @brief ProgrammationEvenementplsJ
     * @param date_ date de début
     * @param debut_ horaire de début
     * @param titre_
     * @param description_
     * @param date_fin_ date de fin
     * @param fin_ horaire de fin
     */
    ProgrammationEvenementplsJ(const QDate& date_, const QTime& debut_, const QString& titre_,
                               const QString& description_, const QDate& date_fin_, const QTime& fin_):
        ProgrammationEvenement(date_, debut_, titre_, description_),date_fin(date_fin_), fin(fin_){}

    const QDate& getDateFin() const {return date_fin;}
    const QTime& getFin() const {return fin;}

    virtual const Duree& getDuree() const {return 24;}

    /**
     * @brief toString : renvoie un QString contenant les informations de la programmation
     * @return
     */
    virtual const QString toString() const;

    /**
     * @brief exportXml : exporte une tache en XML
     * @param stream
     */
    virtual void exportXml(QXmlStreamWriter& stream) const;

    /**
     * @brief type : renvoie le type de la programmation
     * 0 : Programmation évènement 1 jour
     * 1 : Programmation rendez-vous
     * 2 : Programmation Tache Unitaire
     * 3 : Programmation Partie de tâche
     * 4 : Programmation évènement plusieurs jours
     */
    virtual const int type() const {return  4;}

};

#endif // PROGRAMMATIONEVENEMENTPLSJ_H
