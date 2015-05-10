#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include "calendar.h"

class Tache
{
private:
    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;


public:
    Tache(QString id, QString t, QDate dispo, QDate eche): identificateur(id), titre(t),
        disponibilite(dispo), echeance(eche){}

    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e) {
        if (e<disp) throw CalendarException("erreur Tache : date echeance < date disponibilite");
        disponibilite=disp; echeance=e;
    }

};

#endif // TACHE_H
