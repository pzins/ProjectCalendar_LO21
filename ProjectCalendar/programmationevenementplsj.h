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

    virtual ~ProgrammationEvenementplsJ(){}
    const QDate& getDateFin() const {return date_fin;}
    const QTime& getFin() const {return fin;}
    virtual void afficher() const;

    virtual const Duree& getDuree() const {return 24;}
    virtual const QString toString() const;
    virtual bool isEvtPlsJ() const {return true;}
    virtual bool isTache() const {return false;}
    virtual void exportXml(QXmlStreamWriter& stream) const;

    virtual const int type() const {return  4;}

};

#endif // PROGRAMMATIONEVENEMENTPLSJ_H
