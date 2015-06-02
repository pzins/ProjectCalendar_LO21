#include "projetmanager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <iostream>
#include <stdexcept>


ProjetManager* ProjetManager::instance = 0;

ProjetManager::~ProjetManager()
{
    for(std::map<QString, Projet*>::iterator it = map_projet.begin(); it != map_projet.end(); ++it)
        delete (*it).second;
}


void ProjetManager::ajouterProjet(const QString& titre, const QString& description, const QDate& dispo,
                                  const QDate& echeance)
{
    map_projet.insert(std::make_pair(titre,new Projet(titre,description, dispo, echeance)));
}

void ProjetManager::retirerProjet(QString& titre)
{
    Projet* projet = getProjet(titre);
    if(projet)
    {
        map_projet.erase(titre);
        delete projet;
    }
}

void ProjetManager::verification(const QString& titre, const QString& description,
                  const QDate& dispo, const QDate& echeance)
{
    if(titre == "") throw CalendarException("Veuillez entrer un titre");
    if(description == "") throw CalendarException("Veuillez entrer une description");
    if(map_projet.find(titre) != map_projet.end()) throw CalendarException("Nom déjà attribué");
    if(dispo > echeance) throw CalendarException("Disponibilité et echeance incohérentes");
}


QString ProjetManager::getInfo(QModelIndex idx)
{
    QString item = idx.data(0).toString();
    while(idx.parent().isValid()) idx = idx.parent();
    QString parent  = idx.data(0).toString();
    Projet* p = getProjet(parent);
    QString ret;
    if(item != parent)
        ret = p->getTache(item)->info();
    else
        ret = p->info();
    return ret;
}

Projet* ProjetManager::getProjet(const QString &titre)
{
    try
    {
        return map_projet.at(titre);
    }
    catch(out_of_range)
    {
        return 0;
    }
}


void ProjetManager::ajoutItemModel(const QString& titre,const QModelIndex& idx)
{
    QStandardItem* item = new QStandardItem(titre);
    if(idx == model.invisibleRootItem()->index())
    {
        model.invisibleRootItem()->appendRow(item);
    }
    else
    {
        QStandardItem* i = model.itemFromIndex(idx);
        i->appendRow(item);
    }
}

std::vector<QString> ProjetManager::getTacheFilles(const QString& tache, const QString& projet)
{
    QStandardItem* it = model.invisibleRootItem();
    QStandardItem* pro;
    std::vector<QString> res;
    for(int i = 0; i < it->rowCount(); ++i)
    {
        if(it->child(i,0)->data(0).toString() == projet)
        {
            pro = it->child(i,0);
            findItem(pro, tache, res);
        }
    }
    return res;
}

void ProjetManager::findItem(QStandardItem* projet, const QString& item, std::vector<QString>& vec)
{
    if(projet->data(0).toString() == item)
    {
        findChildren(vec, projet);
    }
    for(int i = 0; i < projet->rowCount(); ++i)
    {
        findItem(projet->child(i,0), item, vec);
    }
}


void ProjetManager::findChildren(std::vector<QString>& vec, QStandardItem* item)
{
    vec.push_back(item->data(0).toString());
    for(int i = 0; i < item->rowCount(); ++i)
    {
        findChildren(vec, item->child(i,0));
    }
}


void ProjetManager::supprimerItem(QModelIndex& sel)
{
    QStandardItem* selectedItem = model.itemFromIndex(sel);
    std::vector<QString> vec;
    findChildren(vec, selectedItem);
    QStandardItem* parent = selectedItem;
    while(parent->parent()) parent = parent->parent();
    Projet* p = getProjet(parent->data(0).toString());
    if(p)
    {
        for(std::vector<QString>::iterator it = vec.begin(); it != vec.end(); ++it)
            p->supprimerTache(*it);
    }
    if(parent == selectedItem)
    {
        QString str = parent->data(0).toString();
        retirerProjet(str);
    }
    //delete all children of parent;
    QStandardItem * loopItem = selectedItem; //main loop item
    QList<QStandardItem *> carryItems; //Last In First Out stack of items
    QList<QStandardItem *> itemsToBeDeleted; //List of items to be deleted
    while (loopItem->rowCount())
    {
        itemsToBeDeleted << loopItem->takeRow(0);
        //if the row removed has children:
        if (itemsToBeDeleted.at(0)->hasChildren())
        {
            carryItems << loopItem;                 //put on the stack the current loopItem
            loopItem = itemsToBeDeleted.at(0);      //set the row with children as the loopItem
        }
        //if current loopItem has no more rows but carryItems list is not empty:
        if (!loopItem->rowCount() && !carryItems.isEmpty()) loopItem = carryItems.takeFirst();
    }
    qDeleteAll(itemsToBeDeleted);
    model.removeRow(selectedItem->row(), sel.parent());
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
                QString description;
                QDate disponibilite;
                QDate echeance;
                xml.readNext();                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                            // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "description") {
                            xml.readNext(); description=xml.text().toString();
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
                ajouterProjet(titre,description, disponibilite,echeance);
                //ajoutItemModel(titre, model.invisibleRootItem()->index());
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
        stream.writeTextElement("titre",(*it).getTitre());
        stream.writeTextElement("description",(*it).getDescription());
        stream.writeTextElement("disponibilite",(*it).getDispo().toString(Qt::ISODate));
        stream.writeTextElement("echeance",(*it).getEcheance().toString(Qt::ISODate));
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}



void ProjetManager::saveModel(const QString &f)
{
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("items");

    QStandardItem * item = model.invisibleRootItem();
    save_recursive(*item, stream, "+");
    stream.writeEndElement();
    newfile.close();
}

void ProjetManager::save_recursive(const QStandardItem& item, QXmlStreamWriter& str, QString pere)
{
    str.writeStartElement("item");
    QString ele = item.data(0).toString();
    if(ele == "")
    {
        ele = "*";
    }
    str.writeTextElement("titre",  ele);

    QString s;
    s.setNum(item.rowCount());
    str.writeTextElement("child",s);
    str.writeTextElement("pere",pere);
    str.writeEndElement();
    for(int i = 0; i<item.rowCount(); ++i)
    {
        save_recursive(*item.child(i,0), str, ele);
    }
}




void ProjetManager::appendChild(QStandardItem* item, const QString& pere, const QString& titre)
{
    if(item->data(0).toString() == pere)
    {
        item->appendRow(new QStandardItem(titre));
    }
    else
    {
        for(int i = 0; i < item->rowCount(); ++i)
        {
            appendChild(item->child(i,0), pere, titre);
        }
    }
}

void ProjetManager::loadModel(const QString &f)
{
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
            if(xml.name() == "items") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "item") {
                QString titre;
                QString child;
                QString pere;

                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "item")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            //qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "child") {
                            xml.readNext(); child=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "pere") {
                            xml.readNext(); pere=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                QStandardItem* search_item = 0;
                if(pere == "*")
                {
                    QStandardItem* item = new QStandardItem(titre);
                    model.appendRow(item);

                }
                else if (pere != "*" && pere != "+")
                {

                    QList<QStandardItem*> liste = model.findItems(pere);
                    if(liste.size() > 0)
                    {
                        liste.at(0)->appendRow(new QStandardItem(titre));
                        search_item = liste.at(0);
                    }
                    else
                    {
                        QStandardItem* root = model.invisibleRootItem();
                        for(int i = 0; i < root->rowCount(); ++i)
                        {
                            appendChild(root->child(i,0), pere, titre);
                        }
                    }
                }
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

