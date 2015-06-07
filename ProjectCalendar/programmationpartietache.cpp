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
