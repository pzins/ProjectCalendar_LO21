#include "programmationevenement1j.h"


const QString ProgrammationEvenement1J::toString() const
{
    QString str = ProgrammationEvenement::toString();
    str += "<tr><td><b>Durée</b><td >"+duree.toString()+"</td></td></tr>";
    return str;
}

void ProgrammationEvenement1J::exportXml(QXmlStreamWriter& stream) const
{
    stream.writeStartElement("programmation");
    stream.writeAttribute("type", "0");
    stream.writeTextElement("date",getDate().toString(Qt::ISODate));
    stream.writeTextElement("debut",getDebut().toString());
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    QString str;
    str.setNum(duree.getDureeEnMinutes());
    stream.writeTextElement("duree",str);
    stream.writeEndElement();
}
