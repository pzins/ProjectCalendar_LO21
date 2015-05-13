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
    Duree duree;


public:
    ProgrammationEvenement(const QDate& date_, const QTime& debut_, const QString titre_, const QString description_,
                           const Duree& duree_): Programmation(date_, debut_), titre(titre_), description(description_),
                                                duree(duree_){}

    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}
    const Duree& getDuree() const {return duree;}
};

#endif // PROGRAMMATIONEVENEMENT_H
