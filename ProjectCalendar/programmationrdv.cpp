#include <iostream>
#include "programmationrdv.h"





const QString ProgrammationRdv::toString() const
{
    QString str = ProgrammationEvenement::toString();
    str += "<tr><td><b>Lieu</b><td >"+lieu+"</td></td></tr>";
    str += "<tr><td><b>Participants</b><td >";
    for(int i = 0; i < personne.size(); ++i)
        str += personne.at(i) +"<br>";
    str += "</td></td></tr>";
    return str;
}

void ProgrammationRdv::exportXml(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("programmation");
    stream.writeAttribute("type", "1");
    stream.writeTextElement("date",getDate().toString(Qt::ISODate));
    stream.writeTextElement("debut",getDebut().toString());
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    QString str;
    str.setNum(getDuree().getDureeEnMinutes());
    stream.writeTextElement("duree",str);
    stream.writeTextElement("lieu", getLieu());
    stream.writeTextElement("participants", getPersonne());
    stream.writeEndElement();
}
