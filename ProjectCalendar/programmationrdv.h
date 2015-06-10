#ifndef PROGRAMMATIONRDV_H
#define PROGRAMMATIONRDV_H
#include "programmationevenement1j.h"

/**
 * @class ProgrammationRdv
 * @brief Classe représentant la programmation d'un rendez-vous
 */
class ProgrammationRdv : public ProgrammationEvenement1J
{
private:
    QString lieu;
    QStringList personne;
public:

    /**
     * @brief ProgrammationRdv
     * @param date_ date de début
     * @param debut_ horaire de début
     * @param titre_
     * @param description_
     * @param duree_
     * @param lieu_
     * @param pers_ participants
     */
    ProgrammationRdv(const QDate& date_, const QTime& debut_, const QString titre_, const QString description_,
                     const Duree& duree_, const QString& lieu_, const QString& pers_):
        ProgrammationEvenement1J(date_, debut_, titre_, description_, duree_), lieu(lieu_){
        personne = pers_.split("\n");
    }


    const QString getPersonne() const {
        QString res="";
        for(int i = 0; i < personne.size(); ++i)
        {
            res += personne.at(i);
            if(i != personne.size()-1)
                res += "\n";
        }
    }
    const QString& getLieu() const {return lieu;}

    /**
     * @brief toString : renvoie un QString contenant les informations de la programmation
     * @return
     */
    virtual const QString toString() const;

    /**
     * @brief exportXml : exporte une tache en XML
     * @param stream
     */
    virtual void exportXml(QXmlStreamWriter& stream) const;

    /**
     * @brief type : renvoie le type de la programmation
     * 0 : Programmation évènement 1 jour
     * 1 : Programmation rendez-vous
     * 2 : Programmation Tache Unitaire
     * 3 : Programmation Partie de tâche
     * 4 : Programmation évènement plusieurs jours
     */
    virtual const int type() const {return 1;}


};

#endif // PROGRAMMATIONRDV_H
