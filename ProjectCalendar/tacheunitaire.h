#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H
#include <QString>
#include "calendar.h"
#include "tache.h"

class TacheUnitaire : public Tache
{
    QString identificateur;
    Duree duree;
    bool preemptive;

    TacheUnitaire(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false):
            identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadline),preemptive(preempt){}
    TacheUnitaire(const TacheUnitaire& t);
    TacheUnitaire& operator=(const TacheUnitaire&);
    friend class TacheManager;

public:

    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e) {
        if (e<disp) throw CalendarException("erreur Tache : date echeance < date disponibilite");
        disponibilite=disp; echeance=e;
    }
    bool isPreemptive() const { return preemptive; }
    void setPreemptive() { preemptive=true; }
    void setNonPreemptive() { preemptive=false; }

};

#endif // TACHEUNITAIRE_H
