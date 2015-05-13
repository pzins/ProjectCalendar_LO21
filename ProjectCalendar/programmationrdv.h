#ifndef PROGRAMMATIONRDV_H
#define PROGRAMMATIONRDV_H
#include "programmationevenement.h"

class ProgrammationRdv : public ProgrammationEvenement
{
private:
    QString lieu;
    std::vector<QString> personne;
public:

    ProgrammationRdv(const QDate& date_, const QTime& debut_, const QString titre_, const QString description_,
                     const Duree& duree_, const QString& lieu_): ProgrammationEvenement(date_, debut_, titre_
                      , description_, duree_), lieu(lieu_){}

   const QString& getLieu() const {return lieu;}
   const std::vector<QString>& getPersonne() const {return personne;}
   void ajouterPersonne(const QString& nom);
   void retirerPersonne(const QString& nom);

};

#endif // PROGRAMMATIONRDV_H
