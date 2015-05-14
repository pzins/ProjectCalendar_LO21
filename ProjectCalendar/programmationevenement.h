#ifndef PROGRAMMATIONEVENEMENT_H
#define PROGRAMMATIONEVENEMENT_H
#include <QString>
#include "programmation.h"
#include "calendar.h"

class ProgrammationEvenement : public Programmation
{
private:
    QString titre;
    QString description;


public:
    ProgrammationEvenement(const QDate& date_, const QTime& debut_, const QString& titre_, const QString& description_):
        Programmation(date_, debut_), titre(titre_), description(description_){}

    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}
    virtual void afficher() const =0;


};

#endif // PROGRAMMATIONEVENEMENT_H
