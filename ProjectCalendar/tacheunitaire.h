#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H
#include <QString>
#include "calendar.h"
#include "tache.h"

class TacheUnitaire : public Tache
{
    Duree duree;
    bool preemptive;

    TacheUnitaire(const QString& id, const QString& t, const Duree& dur, const QDate& dispo,
                  const QDate& deadline, bool preempt=false):
            Tache(id, t, dispo, deadline),preemptive(preempt){}
    TacheUnitaire(const TacheUnitaire& t);
    TacheUnitaire& operator=(const TacheUnitaire&);
    friend class TacheManager;

public:



    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }


    bool isPreemptive() const { return preemptive; }
    void setPreemptive() { preemptive=true; }
    void setNonPreemptive() { preemptive=false; }

};

#endif // TACHEUNITAIRE_H
