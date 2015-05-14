#ifndef PROGRAMMATIONRDV_H
#define PROGRAMMATIONRDV_H
#include "programmationevenement1j.h"

class ProgrammationRdv : public ProgrammationEvenement1J
{
private:
    QString lieu;
    std::vector<QString> personne;
public:

    ProgrammationRdv(const QDate& date_, const QTime& debut_, const QString titre_, const QString description_,
                     const Duree& duree_, const QString& lieu_):
        ProgrammationEvenement1J(date_, debut_, titre_, description_, duree_), lieu(lieu_){}

    virtual ~ProgrammationRdv(){}

    const QString& getLieu() const {return lieu;}
    const std::vector<QString>& getPersonne() const {return personne;}
    void ajouterPersonne(const QString& nom);
    void retirerPersonne(const QString& nom);
    virtual void afficher() const;

};

#endif // PROGRAMMATIONRDV_H
