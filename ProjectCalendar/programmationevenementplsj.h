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
    ~ProgrammationEvenementplsJ();
    const QDate& getDateFin() const {return date_fin;}
    const QTime& getFin() const {return fin;}
    virtual void afficher() const
    {
        std::cout << "date : " << getDate().toString().toStdString() << std::endl;
        std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
        std::cout << "titre : " << getTitre().toStdString() << std::endl;
        std::cout << "description : " << getDescription().toStdString() << std::endl;
        std::cout << "date de fin : " << date_fin.toString().toStdString() << std::endl;
        std::cout << "fin : " << fin.toString().toStdString() << std::endl;
    }
};

#endif // PROGRAMMATIONEVENEMENTPLSJ_H
