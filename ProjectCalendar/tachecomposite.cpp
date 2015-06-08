#include "tachecomposite.h"
#include <iostream>

TacheComposite* TacheComposite::ajouterTacheComposite(const QString& titre, const QString& description,
                           const QDate& dispo, const QDate& echeance)
{
    verification(titre, description, dispo, echeance);
    TacheComposite* tc = new TacheComposite(titre, description, dispo, echeance);
    map_tache.insert(std::make_pair(titre, tc));
    return tc;
}


TacheUnitaire* TacheComposite::ajouterTacheUnitaire(const QString& titre, const QString& description,
                          const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive)
{
    verification(titre, description, dispo, echeance);
    TacheUnitaire* tu = new TacheUnitaire(titre, description, dispo, echeance, duree, preemptive);
    map_tache.insert(std::make_pair(titre, tu));
    return tu;
}


TacheComposite::~TacheComposite()
{
    for(std::map<QString, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}

void TacheComposite::verification(const QString& titre, const QString& description,
                  const QDate& dispo, const QDate& echeance)
{
    if(titre == "") throw CalendarException("Veuillez entrer un titre");
    if(description == "") throw CalendarException("Veuillez entrer une description");

    if(echeance > getEcheance()) throw CalendarException("Echéance et échéance de la tache mère sont incohérentes");
    if(dispo < getDispo()) throw CalendarException("Disponibilité et disponibilité de tache mère sont incohérentes");
    if(dispo > echeance) throw CalendarException("Disponibilité et échéance sont incohérentes");
}

void TacheComposite::exportXml(QXmlStreamWriter &stream)
{
    stream.writeStartElement("tache");
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    stream.writeTextElement("disponibilite",getDispo().toString(Qt::ISODate));
    stream.writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    stream.writeEndElement();
}

const QString TacheComposite::info() const
{
    QString str = "<h3 align='center'>Tache Composite</h3>"+Tache::info();
    str += "</table>";
    return str;
}
