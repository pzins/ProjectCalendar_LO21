#include "tacheunitaire.h"
#include <iostream>



void TacheUnitaire::exportXml(QXmlStreamWriter &stream)
{
    stream.writeStartElement("tache");
    stream.writeAttribute("preemptive", isPreemptive()?"true":"false");
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    stream.writeTextElement("disponibilite",getDispo().toString(Qt::ISODate));
    stream.writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    QString str;
    str.setNum(duree.getDureeEnMinutes());
    stream.writeTextElement("duree",str);
    stream.writeEndElement();
}

QString TacheUnitaire::info() const
{
    QString str = "<h3 align='center'>Tache Unitaire</h3>"+Tache::info();
    str += "<tr><td><b>Durée</b><td >"+duree.toString()+"</td></td></tr>";
    str += "</table>";

    return str;
}
