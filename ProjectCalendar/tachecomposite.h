#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include <map>
#include "tache.h"
#include "tacheunitaire.h"



class TacheComposite : public Tache
{
private:
    std::map<QString, Tache*> map_tache;

public:

    void retirerTache(Tache& t);
    TacheComposite *ajouterTacheComposite(const QString& titre, const QString& description, const QDate& dispo,
                               const QDate& echeance);
    void ajouterTacheUnitaire(const QString& titre, const QString& description, const QDate& dispo,
                              const QDate& echeance, const Duree& duree, bool preemptive=false);

    std::map<QString, Tache*>& getTache() {return map_tache;}

    TacheComposite(const QString& titre_, const QString& description_, const QDate& dispo_,
                   const QDate& echeance_):
        Tache(titre_, description_, dispo_, echeance_){}
    ~TacheComposite();
    virtual void afficher(QStandardItem* it) ;

    virtual void afficherComposite(QComboBox& c);
    virtual void exportXml(QXmlStreamWriter& stream);



    class Iterator
    {
        friend class TacheComposite;
        std::map<QString, Tache*>::iterator courant;
        Iterator(std::map<QString, Tache*>::iterator deb) : courant(deb){}
    public:
        Iterator() : courant(0){}
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
