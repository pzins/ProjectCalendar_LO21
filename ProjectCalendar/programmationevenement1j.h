#ifndef PROGRAMMATIONEVENEMENT1J_H
#define PROGRAMMATIONEVENEMENT1J_H
#include "programmationevenement.h"

/**
 * @class ProgrammationEvenement1J
 * @brief Classe représentant la programmation d'un évènement sur 1 jour
 */
class ProgrammationEvenement1J : public ProgrammationEvenement
{
private:
    Duree duree;

public:
    /**
     * @brief ProgrammationEvenement1J
     * @param date_ date de début
     * @param debut_ horaire de début
     * @param titre_
     * @param description_
     * @param duree_
     */
    ProgrammationEvenement1J(const QDate& date_, const QTime& debut_, const QString& titre_, const QString& description_,
                             const Duree& duree_): ProgrammationEvenement(date_, debut_, titre_, description_),
                            duree(duree_){}


    virtual const Duree& getDuree() const {return duree;}

    /**
     * @brief toString : retourne un QString contenant les informations de la pogrammation
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
    virtual const int type() const {return 0;}



};

#endif // PROGRAMMATIONEVENEMENT1J_H
