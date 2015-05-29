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

void TacheComposite::retirerTache(Tache& tache)
{
    //à voir en fct de si suppr tache ou juste enlève de cette tachecompo
    //voir cycles de vies liés ou pas
    /*
    std::map<unsigned int, Tache*>::iterator it = map_tache.find(tache.getId());
    Tache* tu = (*it).second;
    map_tache.erase(it);
    delete tu;*/
}

void TacheComposite::afficher(QStandardItem* item)
{
    QStandardItem* i = new QStandardItem(getTitre());
    item->appendRow(i);
    for(TacheComposite::Iterator it = begin(); it != end(); ++it)
    {
        (*it).afficher(i);
    }

    /*std::cout << "id: " << getId() << std::endl;
    std::cout << "titre: " << getTitre().toStdString() << std::endl;
    std::cout << "description: " << getDescription().toStdString() << std::endl;
    std::cout << "dispo: " << getDispo().toString().toStdString() << std::endl;
    std::cout << "echeance: " << getEcheance().toString().toStdString() << std::endl;
    std::cout << "tache contenues: " << std::endl;
    for (std::map<unsigned int, Tache*>::const_iterator it=map_tache.begin(); it!=map_tache.end(); ++it)
    {
        it->second->afficher();
    }*/
}

void TacheComposite::afficherComposite(QComboBox& c)
{
    c.addItem(getTitre(), getTitre());
    for(TacheComposite::Iterator it = begin(); it != end(); ++it)
        (*it).afficherComposite(c);
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

