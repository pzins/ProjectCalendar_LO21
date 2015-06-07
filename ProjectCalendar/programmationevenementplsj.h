#ifndef PROGRAMMATIONEVENEMENTPLSJ_H
#define PROGRAMMATIONEVENEMENTPLSJ_H
#include "programmationevenement.h"


class ProgrammationEvenementplsJ : public ProgrammationEvenement
{
private:
    QDate date_fin;
    QTime fin;
public:
    ProgrammationEvenementplsJ(const QDate& date_, const QTime& debut_, const QString& titre_,
                               const QString& description_, const QDate& date_fin_, const QTime& fin_):
        ProgrammationEvenement(date_, debut_, titre_, description_),date_fin(date_fin_), fin(fin_){}

    virtual ~ProgrammationEvenementplsJ(){}
    const QDate& getDateFin() const {return date_fin;}
    const QTime& getFin() const {return fin;}
    virtual void afficher() const;
    virtual bool isEvt1j() const {return false;}

    virtual const Duree& getDuree() const {return 24;}
    virtual const QString toString() const;
    virtual bool isEvtPlsJ() const {return true;}
    virtual bool isTache() const {return false;}
    virtual void exportXml(QXmlStreamWriter& stream) const;


};

#endif // PROGRAMMATIONEVENEMENTPLSJ_H
