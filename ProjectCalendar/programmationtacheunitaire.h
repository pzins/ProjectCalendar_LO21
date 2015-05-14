#ifndef PROGRAMMATIONTACHEUNITAIRE_H
#define PROGRAMMATIONTACHEUNITAIRE_H
#include "programmation.h"
#include "tacheunitaire.h"

class ProgrammationTacheUnitaire : public Programmation
{
private:
    const TacheUnitaire* tache;

public:
    ProgrammationTacheUnitaire(const QDate date_, const QTime& debut_, const TacheUnitaire& tache_):
        Programmation(date_, debut_), tache(&tache_){}
    const TacheUnitaire* getTache() const {return tache;}

    virtual void afficher() const
    {
        std::cout << "date : " << getDate().toString().toStdString() << std::endl;
        std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
    }

};

#endif // PROGRAMMATIONTACHEUNITAIRE_H
