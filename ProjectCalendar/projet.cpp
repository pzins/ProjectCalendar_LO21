#include "projet.h"
#include "projetmanager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <iostream>

void Projet::ajouterTache(QChar type, const QString& titre, const QString& description, const QDate& dispo,
                          const QDate& echeance, const Duree& duree, bool preemptive)
{
    if(type == 'U')
    {
        Tache* tu = new TacheUnitaire(titre, description, dispo, echeance, duree, preemptive);
        map_tache.insert(std::make_pair(titre, tu));
    }
    else if(type == 'C')
    {
        Tache* tc =  new TacheComposite(titre, description, dispo, echeance);
        map_tache.insert(std::make_pair(titre,tc));
    }
}


void Projet::supprimerTache(QString& titre)
{
    map_tache.erase(titre);
}

Projet::~Projet()
{
    for(std::map<QString, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}



void Projet::load(const QString& f)
{
    QFile fin(f);
    std::cout << f.toStdString() << std::endl;
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "taches") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "tache") {
                QString parent_tache;
                bool has_parent_composite = false;

                QString titre;
                QString description;
                QDate disponibilite;
                QDate echeance;
                Duree duree;
                bool preemptive;
                bool isComposite = true;
                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("preemptive")) {
                    QString val =attributes.value("preemptive").toString();
                    preemptive=(val == "true" ? true : false);
                    isComposite = false;
                }
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "description") {
                            xml.readNext(); description=xml.text().toString();
                        }
                        // We've found disponibilite
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found duree
                        if(xml.name() == "duree") {
                            xml.readNext();
                            duree.setDuree(xml.text().toString().toUInt());
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                if(!isComposite)
                    ajouterTache(QChar('U'), titre, description, disponibilite, echeance, duree, preemptive);
                else
                    ajouterTache(QChar('C'), titre, description, disponibilite, echeance, duree, preemptive);

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void Projet::save(const QString& t)
{
    QFile newfile(t);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for(Projet::Iterator it = begin(); it != end(); ++it){
        (*it).exportXml(stream);
    }
    stream.writeEndDocument();
    newfile.close();
}


