#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include <map>
#include "tache.h"
#include "tacheunitaire.h"


/**
 * @class TacheComposite
 * @brief Classe abstraite représentant une TacheComposite
 */
class TacheComposite : public Tache
{
private:
    std::map<QString, Tache*> map_tache;

public:

    /**
     * @brief ajouterTacheComposite : ajout d'un tache composite
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     * @return
     */
    TacheComposite* ajouterTacheComposite(const QString& titre, const QString& description, const QDate& dispo,
                               const QDate& echeance);
    /**
     * @brief ajouterTacheUnitaire : ajout d'une tache unitaire
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     * @param duree
     * @param preemptive
     * @return
     */
    TacheUnitaire* ajouterTacheUnitaire(const QString& titre, const QString& description, const QDate& dispo,
                              const QDate& echeance, const Duree& duree, bool preemptive=false);

    /**
     * @brief verification : vérification lors de l'ajout d'un tache
     * @param titre
     * @param description
     * @param dispo
     * @param echeance
     */
    void verification(const QString& titre, const QString& description,
                      const QDate& dispo, const QDate& echeance);

    std::map<QString, Tache*>& getTache() {return map_tache;}

    TacheComposite(const QString& titre_, const QString& description_, const QDate& dispo_,
                   const QDate& echeance_):
        Tache(titre_, description_, dispo_, echeance_){}

    virtual ~TacheComposite();

    virtual void exportXml(QXmlStreamWriter& stream);
    virtual bool isComposite() const{return true;}
    virtual const QString info() const;



    /**
     * @class Iterator
     * @brief Iterator de TacheComposite, parcourt les taches de TacheComposite
     */
    class Iterator
    {
        std::map<QString, Tache*>::iterator courant;
    public:
        Iterator(std::map<QString, Tache*>::iterator deb) : courant(deb){}
        Tache& operator*() const {return *(courant->second);}
        Iterator& operator++(){++courant; return *this;}
        Iterator operator++(int i){
            Iterator old = *this;
            ++courant;
            return old;
        }
        bool operator==(Iterator it) const{
            return courant == it.courant;
        }
        bool operator!=(Iterator it) const{
            return courant != it.courant;
        }
    };
    Iterator begin(){return Iterator(map_tache.begin());}
    Iterator end(){return Iterator(map_tache.end());}
};




#endif // TACHECOMPOSITE_H
