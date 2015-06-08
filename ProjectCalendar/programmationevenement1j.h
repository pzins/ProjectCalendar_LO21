#ifndef PROGRAMMATIONEVENEMENT1J_H
#define PROGRAMMATIONEVENEMENT1J_H
#include "programmationevenement.h"
#include "duree.h"

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

    virtual const QString toString() const;
    virtual bool isEvtPlsJ() const {return false;}
    virtual bool isTache() const {return false;}

    virtual void exportXml(QXmlStreamWriter& stream) const;

    virtual const int type() const {return 0;}



};

#endif // PROGRAMMATIONEVENEMENT1J_H
