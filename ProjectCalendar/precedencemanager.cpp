#include "precedencemanager.h"
#include "calendarexception.h"
#include "projetmanager.h"
#include <iostream>


PrecedenceManager* PrecedenceManager::instance = 0;


PrecedenceManager::~PrecedenceManager()
{
    for(std::set<Precedence*, MyComp>::iterator it = set_precedence.begin(); it != set_precedence.end(); ++it)
        delete (*it);
}


void PrecedenceManager::ajouterPrecedence(Tache &pred_, Tache &succ_, Projet& projet_)
{
    Precedence* pred = new Precedence(pred_,succ_, projet_);
    if(!set_precedence.insert(pred).second)
    {
        delete pred;
        throw CalendarException("Précédence déjà présente");
    }
    else if (containsInverse(*pred))
    {
        delete pred;
        throw CalendarException("Précédence non cohérente");
    }
    else
    {
        notifier();
    }
}

bool PrecedenceManager::containsInverse(const Precedence &p) const
{
    for(PrecedenceManager::ConstIterator it = begin(); it != end(); ++it)
    {
        if(p.isInverse(*it))
            return true;
    }
    return false;
}


void PrecedenceManager::retirerPrecedence(Precedence &p)
{
    for(std::set<Precedence*, MyComp>::iterator it = set_precedence.begin(); it != set_precedence.end(); ++it)
    {
        if(p == *(*it))
        {
            set_precedence.erase(it);
            notifier();
            break;
        }
    }
}

std::vector<Precedence*> PrecedenceManager::findPrecedence(Projet* p, Tache* t)
{
    std::vector<Precedence*> vec;
    if(p)
    {
        for(PrecedenceManager::Iterator it = begin(); it != end(); ++it)
        {
            if((*it) == *p && ((*it) == *t) || !t)
            {
                vec.push_back(&*it);
            }
        }
    }
    return vec;
}

void PrecedenceManager::update(const QString& s1, const QString& s2)
{
    Projet* p = ProjetManager::getInstance().getProjet(s1);
    if(!p) return;
    Tache* t = p->getTache(s2);
    std::vector<Precedence*> vec = findPrecedence(p, t);
    for(std::vector<Precedence*>::iterator it = vec.begin(); it != vec.end(); ++it)
         retirerPrecedence(*(*it));
}

void PrecedenceManager::notifier(const QString& s1, const QString& s2)
{
    for(Observable::Iterator it = getObs().begin(); it != getObs().end(); ++it)
        (*it).update(s1,s2);
}


void PrecedenceManager::save(const QString& f, bool contraintes){
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("precedences");
    for(PrecedenceManager::Iterator it = begin(); it != end(); ++it){
        stream.writeStartElement("precedence");
        QString str;
        stream.writeTextElement("projet",(*it).getProjet().getTitre());
        stream.writeTextElement("anterieure",(*it).getPred().getTitre());
        stream.writeTextElement("posterieure",(*it).getSucc().getTitre());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void PrecedenceManager::load(const QString& f){
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
            if(xml.name() == "precedences") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "precedence") {
                QString projet;
                QString anterieure;
                QString posterieure;
                xml.readNext();                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "precedence")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                            // We've found titre.
                        if(xml.name() == "projet") {
                            xml.readNext(); projet=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "anterieure") {
                            xml.readNext(); anterieure=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "posterieure") {
                            xml.readNext(); posterieure=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                Projet* p = ProjetManager::getInstance().getProjet(projet);
                Tache* ant = p->getTache(anterieure);
                Tache* post = p->getTache(posterieure);
                ajouterPrecedence(*ant, *post, *p);
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
