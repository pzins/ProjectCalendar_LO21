#include "programmationtacheunitaire.h"


void ProgrammationTacheUnitaire::afficher() const
{
    std::cout << "date : " << getDate().toString().toStdString() << std::endl;
    std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
}


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
