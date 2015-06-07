#ifndef PROGRAMMATIONEVENEMENT1J_H
#define PROGRAMMATIONEVENEMENT1J_H
#include "programmationevenement.h"
#include "duree.h"

class ProgrammationEvenement1J : public ProgrammationEvenement
{
private:
    Duree duree;

public:
    ProgrammationEvenement1J(const QDate& date_, const QTime& debut_, const QString& titre_, const QString& description_,
                             const Duree& duree_): ProgrammationEvenement(date_, debut_, titre_, description_),
                            duree(duree_){}

    virtual ~ProgrammationEvenement1J(){}

    virtual const Duree& getDuree() const {return duree;}
    virtual void afficher() const;
    virtual bool isEvt1j() const {return true;}
    virtual const QString toString() const;
    virtual bool isEvtPlsJ() const {return false;}
    virtual bool isTache() const {return false;}

    virtual void exportXml(QXmlStreamWriter& stream) const;

    virtual const int type() const {return 0;}



};

#endif // PROGRAMMATIONEVENEMENT1J_H
