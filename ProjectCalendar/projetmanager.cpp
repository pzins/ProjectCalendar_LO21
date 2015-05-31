#include "projetmanager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <iostream>
#include <stdexcept>


ProjetManager* ProjetManager::instance = 0;


void ProjetManager::ajouterProjet(const QString& titre, const QString& description, const QDate& dispo,
                                  const QDate& echeance)
{
    map_projet.insert(std::make_pair(titre,new Projet(titre,description, dispo, echeance)));
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




void ProjetManager::update()
{
/*
    model.clear();
    for(ProjetManager::Iterator it = begin(); it != end(); ++it)
    {
        QStandardItem* item = new QStandardItem((*it).getTitre());
        model.appendRow(item);
        for(Projet::Iterator ite = (*it).begin(); ite != (*it).end(); ++ite)
        {
           (*ite).afficher(item);
        }
    }*/
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


void ProjetManager::findChildren(std::vector<QString>& vec, QModelIndex& selected)
{
    QStandardItem* selectedItem = model.itemFromIndex(selected);
    for(int i = 0; i < selectedItem->rowCount(); ++i)
    {
        QModelIndex child = model.index(i,0,selected);
        vec.push_back(child.data().toString());
        QStandardItem* item = model.itemFromIndex(child);
        if(item->hasChildren())
        {
            findChildren(vec, child);
        }
    }
}


void ProjetManager::supprimerItem(QModelIndexList& sel)
{
    QModelIndex selected = sel.at(0);
    QStandardItem* selectedItem = model.itemFromIndex(selected);
    std::vector<QString> vec;
    findChildren(vec, selected);
    QModelIndex idx_parent = selected;
    while(idx_parent.parent().data().toString() != "") idx_parent = idx_parent.parent();

    Projet* p = getProjet(idx_parent.data().toString());
    if(p)
    {
        for(std::vector<QString>::iterator it = vec.begin(); it != vec.end(); ++it)
            p->supprimerTache(*it);
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
    model.removeRow(selectedItem->row(), selected.parent());
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
    rec_fct(*item, stream, "+");
    stream.writeEndElement();
    newfile.close();
}

void ProjetManager::rec_fct(const QStandardItem& item, QXmlStreamWriter& str, QString pere)
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
        rec_fct(*item.child(i,0), str, ele);
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
                        QStandardItem* res;
                        QStandardItem* root = model.invisibleRootItem();
                        for(int i = 0; i < root->rowCount(); ++i)
                        {
                            res = getChild(root->child(i,0), pere, titre);
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

QStandardItem* ProjetManager::getChild(QStandardItem* item, QString& pere, QString ele)
{
    if(item->data(0).toString() == pere)
    {
        item->appendRow(new QStandardItem(ele));
    }
    else
    {
        for(int i = 0; i < item->rowCount(); ++i)
        {
            getChild(item->child(i,0), pere, ele);
        }
    }
}
