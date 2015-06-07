#ifndef PROGRAMMATIONRDV_H
#define PROGRAMMATIONRDV_H
#include "programmationevenement1j.h"

class ProgrammationRdv : public ProgrammationEvenement1J
{
private:
    QString lieu;
    QStringList personne;
public:

    ProgrammationRdv(const QDate& date_, const QTime& debut_, const QString titre_, const QString description_,
                     const Duree& duree_, const QString& lieu_, const QString& pers_):
        ProgrammationEvenement1J(date_, debut_, titre_, description_, duree_), lieu(lieu_){
        personne = pers_.split("\n");
    }

    virtual ~ProgrammationRdv(){}

    QString getPersonne() const {
        QString res="";
        for(int i = 0; i < personne.size(); ++i)
        {
            res += personne.at(i);
            if(i != personne.size()-1)
                res += "\n";
        }
    }
    const QString& getLieu() const {return lieu;}
    void ajouterPersonne(const QString& nom);
    void retirerPersonne(const QString& nom);
    virtual void afficher() const;
    virtual const QString toString() const;
    virtual bool isEvtPlsJ() const {return false;}
    virtual void exportXml(QXmlStreamWriter& stream) const;

    virtual const int type() const {return 1;}


};

#endif // PROGRAMMATIONRDV_H
