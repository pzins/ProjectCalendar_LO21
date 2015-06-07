#include "programmationevenementplsj.h"


void ProgrammationEvenementplsJ::afficher() const
{
    std::cout << "date : " << getDate().toString().toStdString() << std::endl;
    std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
    std::cout << "titre : " << getTitre().toStdString() << std::endl;
    std::cout << "description : " << getDescription().toStdString() << std::endl;
    std::cout << "date de fin : " << date_fin.toString().toStdString() << std::endl;
    std::cout << "fin : " << fin.toString().toStdString() << std::endl;
}

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
