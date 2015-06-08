#include "programmationtacheunitaire.h"




void ProgrammationTacheUnitaire::exportXml(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("programmation");
    stream.writeAttribute("type", "2");
    stream.writeTextElement("date",getDate().toString(Qt::ISODate));
    stream.writeTextElement("debut",getDebut().toString());
    stream.writeTextElement("projet", projet);
    stream.writeTextElement("tache", tache->getTitre());
    stream.writeEndElement();
}

const QString ProgrammationTacheUnitaire::toString() const
{
    QString str = Programmation::toString();
    str += "<tr><td><b>Titre</b><td >"+tache->getTitre()+"</td></td></tr>";
    str += "<tr><td><b>Description</b><td >"+tache->getDescription()+"</td></td></tr>";
    str += "<tr><td><b>Durée</b><td >"+tache->getDuree().toString()+"</td></td></tr>";
    QString s = (tache->isPreemptive()? "true" : "false");
    str += "<tr><td><b>Préemptive</b><td >"+s+"</td></td></tr>";
    return str;

}
