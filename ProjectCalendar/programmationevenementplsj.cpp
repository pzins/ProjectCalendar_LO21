#include "programmationevenementplsj.h"


const QString ProgrammationEvenementplsJ::toString() const
{
    QString str = ProgrammationEvenement::toString();
    str += "<tr><td><b>Date fin</b><td >"+date_fin.toString()+"</td></td></tr>";
    str += "<tr><td><b>Fin</b><td >"+fin.toString()+"</td></td></tr>";
    return str;
}

void ProgrammationEvenementplsJ::exportXml(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("programmation");
    stream.writeAttribute("type", "4");
    stream.writeTextElement("date",getDate().toString(Qt::ISODate));
    stream.writeTextElement("debut",getDebut().toString());
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    stream.writeTextElement("datefin",date_fin.toString(Qt::ISODate));
    stream.writeTextElement("fin",fin.toString());
    stream.writeEndElement();
}
