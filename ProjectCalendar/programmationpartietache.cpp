#include "programmationpartietache.h"


void ProgrammationPartieTache::afficher() const
{
    ProgrammationTacheUnitaire::afficher();
    std::cout << "numero : " << numero << std::endl;
    std::cout << "nom partie : " << nom_partie.toStdString() << std::endl;
    QTextStream a(stdout);
    duree.afficher(a);
}

void ProgrammationPartieTache::exportXml(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("programmation");
    stream.writeAttribute("type", "3");
    stream.writeTextElement("date",getDate().toString(Qt::ISODate));
    stream.writeTextElement("debut",getDebut().toString());
    QString str;
    str.setNum(numero);
    stream.writeTextElement("numero",str);
    stream.writeTextElement("nom", nom_partie);
    QString str2;
    str2.setNum(duree.getDureeEnMinutes());
    stream.writeTextElement("duree",str2);
    stream.writeTextElement("projet", getProjet() );
    stream.writeTextElement("tache", getTache()->getTitre());
    stream.writeEndElement();
}

const QString ProgrammationPartieTache::toString() const
{
    QString str = ProgrammationTacheUnitaire::toString();
    QString tmp = QString::number(numero);
    str += "<tr><td><b>Numéro</b><td >"+tmp+"</td></td></tr>";
    str += "<tr><td><b>Nom</b><td >"+nom_partie+"</td></td></tr>";
    str += "<tr><td><b>Durée partie</b><td >"+duree.toString()+"</td></td></tr>";
    return str;

}
