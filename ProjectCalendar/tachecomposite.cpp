#include "tachecomposite.h"



void TacheComposite::verification(const QString& titre, const QString& description,
                  const QDate& dispo, const QDate& echeance)
{
    if(titre == "") throw CalendarException("Veuillez entrer un titre");
    if(description == "") throw CalendarException("Veuillez entrer une description");

    if(echeance > getEcheance()) throw CalendarException("Echéance et échéance de la tache mère sont incohérentes");
    if(dispo < getDispo()) throw CalendarException("Disponibilité et disponibilité de tache mère sont incohérentes");
    if(dispo > echeance) throw CalendarException("Disponibilité et échéance sont incohérentes");
}

void TacheComposite::exportXml(QXmlStreamWriter &stream) const
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
