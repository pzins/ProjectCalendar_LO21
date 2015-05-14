#ifndef PROGRAMMATIONEVENEMENT1J_H
#define PROGRAMMATIONEVENEMENT1J_H
#include "programmationevenement.h"
#include "calendar.h"

class ProgrammationEvenement1J : public ProgrammationEvenement
{
private:
    Duree duree;

public:
    ProgrammationEvenement1J(const QDate& date_, const QTime& debut_, const QString& titre_, const QString& description_,
                             const Duree& duree_): ProgrammationEvenement(date_, debut_, titre_, description_),
                            duree(duree_){}
    ~ProgrammationEvenement1J();
    const Duree& getDuree() const {return duree;}
    virtual void afficher() const
    {
        std::cout << "date : " << getDate().toString().toStdString() << std::endl;
        std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
        std::cout << "titre : " << getTitre().toStdString() << std::endl;
        std::cout << "description : " << getDescription().toStdString() << std::endl;
        QTextStream a(stdout);
        duree.afficher(a);
    }
};

#endif // PROGRAMMATIONEVENEMENT1J_H
