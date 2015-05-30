#include "tachecomposite.h"
#include <iostream>

TacheComposite* TacheComposite::ajouterTacheComposite(const QString& titre, const QString& description,
                           const QDate& dispo, const QDate& echeance)
{
    verification(titre, description, dispo, echeance);
    TacheComposite* tc = new TacheComposite(titre, description, dispo, echeance);
    map_tache.insert(std::make_pair(titre, tc));
    return tc;
}


TacheUnitaire* TacheComposite::ajouterTacheUnitaire(const QString& titre, const QString& description,
                          const QDate& dispo, const QDate& echeance, const Duree& duree, bool preemptive)
{
    verification(titre, description, dispo, echeance);
    TacheUnitaire* tu = new TacheUnitaire(titre, description, dispo, echeance, duree, preemptive);
    map_tache.insert(std::make_pair(titre, tu));
    return tu;
}


TacheComposite::~TacheComposite()
{
    for(std::map<QString, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}

void TacheComposite::exportXml(QXmlStreamWriter &stream)
{
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    stream.writeTextElement("disponibilite",getDispo().toString(Qt::ISODate));
    stream.writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    stream.writeEndElement();
    for(TacheComposite::Iterator it = begin(); it != end(); ++it)
    {
        stream.writeStartElement("tache");
        stream.writeAttribute("parent_tache", getTitre());
        (*it).exportXml(stream);
        stream.writeEndElement();
    }
}

