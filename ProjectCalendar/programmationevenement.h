#ifndef PROGRAMMATIONEVENEMENT_H
#define PROGRAMMATIONEVENEMENT_H
#include "programmation.h"

/**
 * @class ProgrammationEvenement
 * @brief Classe abstraite représentant une programmation d'évènement dans un agenda
 */
class ProgrammationEvenement : public Programmation
{
private:
    QString titre;
    QString description;


public:
    /**
     * @brief ProgrammationEvenement
     * @param date_ date de début
     * @param debut_ horaire de début
     * @param titre_
     * @param description_
     */
    ProgrammationEvenement(const QDate& date_, const QTime& debut_, const QString& titre_, const QString& description_):
        Programmation(date_, debut_), titre(titre_), description(description_){}


    virtual const Duree& getDuree() const =0;

    virtual const QString& getTitre() const {return titre;}
    virtual const QString& getDescription() const {return description;}

    /**
     * @brief toString : retourne un QString contenant les informations de la programmation
     * @return
     */
    virtual const QString toString() const;


};

#endif // PROGRAMMATIONEVENEMENT_H
