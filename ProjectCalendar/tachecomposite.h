#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include "tacheunitaire.h"


/**
 * @class TacheComposite
 * @brief Classe abstraite représentant une TacheComposite
 */
class TacheComposite : public Tache
{
public:

    /**
     * @brief verification : vérification lors de l'ajout d'un tache
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     */
    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance);


    TacheComposite(const QString& titre_, const QString& description_, const QDate& dispo_,
                   const QDate& echeance_):  Tache(titre_, description_, dispo_, echeance_){}


    virtual void exportXml(QXmlStreamWriter& stream) const;
    virtual bool isComposite() const{return true;}
    virtual const QString info() const;
};




#endif // TACHECOMPOSITE_H
