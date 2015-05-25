#include "projetmanager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <iostream>

unsigned int ProjetManager::nb_projet = 0;

ProjetManager* ProjetManager::instance = 0;


void ProjetManager::ajouterProjet(const QString& titre, const QDate& dispo,
                                  const QDate& echeance)
{
    map_projet.insert(std::make_pair(titre,new Projet(nb_projet, titre, dispo, echeance)));
    ++nb_projet;
}

void ProjetManager::retirerProjet(QString& titre)
{
    //a voir cycles vies liés?
    //ProjetManager::Iterator it = map_projet.find(projet.getId());
    //Projet* tu = (*it).second;
    //map_projet.erase(it);
    //delete tu;
    //nb_projet--;
    //map_projet.at(titre)->setId(projet.getId());
}


Projet& ProjetManager::getProjet(const QString &titre)
{
    return *map_projet.at(titre);
}


void ProjetManager::remplirModel()
{
    model.clear();
    for(ProjetManager::Iterator it = begin(); it != end(); ++it)
    {
        QStandardItem* item = new QStandardItem((*it).getTitre());
        model.appendRow(item);
        for(Projet::Iterator ite = (*it).begin(); ite != (*it).end(); ++ite)
        {
           (*ite).afficher(item);
        }
    }
}


void ProjetManager::load(const QString& f){
    //qDebug()<<"debut load\n";
    //this->~TacheManager();
    QFile fin(f);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "projets") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "projet") {
                QString titre;
                QDate disponibilite;
                QDate echeance;
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                            // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
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
                    }
                    // ...and next...
                    xml.readNext();
                }
                ajouterProjet(titre,disponibilite,echeance);
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

void ProjetManager::save(const QString& f){
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("projets");
    for(ProjetManager::Iterator it = begin(); it != end(); ++it){
        stream.writeStartElement("projet");
        QString str;
        str.setNum((*it).getId());
        stream.writeAttribute("id", str);
        stream.writeTextElement("titre",(*it).getTitre());
        stream.writeTextElement("disponibilite",(*it).getDispo().toString(Qt::ISODate));
        stream.writeTextElement("echeance",(*it).getEcheance().toString(Qt::ISODate));
        str.setNum(ProjetManager::nb_projet);
        stream.writeTextElement("nombreprojet", str);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

