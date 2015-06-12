#include "agenda.h"
#include "projetmanager.h"
#include <iostream>
Agenda* Agenda::instance = 0;



void Agenda::ajouterScene(const QString& jour, const QDate& date, qreal h, qreal w, QObject *parent)
{
    //8h-22h => 14H => 840 min
    JourScene* js = new JourScene(jour,date,0,0,w-2,h-2,840,parent);
    ajouterObservateur(js);
    scenes.push_back(js);
}



Agenda::~Agenda()
{
    //suppression des scenes
    for(unsigned int i=0; i<scenes.size(); i++) delete scenes[i];
    std::set<Programmation*, ProgComp>::iterator it;
    std::set<Programmation*, ProgComp>::iterator end;
    //suppression des programmations
    while(it != end)
    {
        std::set<Programmation*, ProgComp>::iterator tmp = it;
        ++it;
        delete *tmp;
    }

}

void Agenda::notifier(const QString& s1, const QString& s2) const
{
    for(Observable::Iterator it = getObs().begin(); it != getObs().end(); ++it)
    {
        (*it).update();
    }
}

void Agenda::ajouterProgrammationPlsJour(const QDate& date, const QString titre, const QString& desc,
                                         const QTime& debut, const QDate& date_fin, const QTime& fin)
{
    ProgrammationEvenementplsJ* p = new ProgrammationEvenementplsJ(date, debut, titre, desc, date_fin, fin);
    verifProgrammation(p);
    if(set_prog.insert(p).second == false)
    {
        delete p;
        throw CalendarException("Erreur, Agenda, une programmation existe à cette heure");
    }
    notifier();
}



void Agenda::verifProgrammation(Programmation* p)
{
    for(std::set<Programmation*, ProgComp>::iterator it = set_prog.begin(); it != set_prog.end(); ++it)
    {
        //si evt sur plusieurs jours : vérification des chevauchements
        if(p->type() == 4)
        {
            ProgrammationEvenementplsJ* tmp = dynamic_cast<ProgrammationEvenementplsJ*>(p);
            if (tmp->getDateFin() == (*it)->getDate())
            if(QDateTime(tmp->getDateFin(), tmp->getFin()) > QDateTime((*it)->getDate(), (*it)->getDebut()) &&
                    QDateTime(tmp->getDate(), tmp->getDebut()) < QDateTime((*it)->getDate(), (*it)->getDebut()))
            {
                throw CalendarException("Chevauchement de programmations");
            }
        }
        //sinon : vérification pas de chevauchement
        else
        {
            //début de nouvelle tache avant fin d'une ancienne
            if(p->getDate() == (*it)->getDate() && (*it)->getDebut() < p->getDebut())
            {
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > p->getDebut())
                {
                    throw CalendarException("Chevauchement de programmations");
                }
            }
            //fin de nouvelle tache après début d'une ancienne
            else if(p->getDate() == (*it)->getDate() && (*it)->getDebut() > p->getDebut())
            {
                QTime fin = p->getDebut().addSecs(p->getDuree().getDureeEnMinutes() * 60);
                if(fin > (*it)->getDebut())
                {
                    throw CalendarException("Chevauchement de programmations");
                }
            }
        }
    }
}

void Agenda::ajouterProgrammationPartieTache(std::vector<QDate>& vec_date, std::vector<QString>& vec_titre,
                                             std::vector<QTime>& vec_debut, std::vector<Duree>& vec_duree,
                                             TacheUnitaire* tache, Projet* projet)
{
    std::vector<ProgrammationPartieTache*> vec;
    try
    {
        //vérification et insertion de programmations pour chaque parties de la tache dans un vector temporaire
        //d'abord on vérifie tout pour que si il y a un problème lors de la programmation d'une partie
        //aucune partie ne soit programmée (tout ou rien)
        for(int i = 0; i < vec_date.size(); ++i)
        {
            vec.push_back(new ProgrammationPartieTache(vec_date.at(i), vec_debut.at(i), *tache, i+1,
                                                   vec_titre.at(i), vec_duree.at(i), *projet));
            verifProgrammation(vec.at(i));
        }
        //insertion de toutes les parties dans l'agenda
        for(int i = 0; i < vec.size(); ++i)
        {
            set_prog.insert(vec.at(i));
        }
        vec.at(0)->getTache()->setIsProgrammed(true);
    }
    catch(CalendarException e)
    {
        QMessageBox::critical(0, "Erreur", e.getInfo());
        //suppression des parties déjà créees qui ne seront pas ajoutées car il y a eu une erreur pour l'une d'entre elles
        for(int i = 0; i < vec.size(); ++i)
        {
            delete vec.at(i);
        }
    }
    notifier();
}


void Agenda::ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc,
                                  const QTime& debut, const Duree& duree, const QString& lieu, const QString& pers,
                                  TacheUnitaire* tache, Projet* projet, int num_partie, const QString nom_partie)
{
    Programmation* p;
    //création du bon type d'évènement en fonction de l'entier type
    //0 : Evt 1 jour, 1 : rendez-vous, 2 : tache unitaire, 3 : partie de tache
    if(type == 0)
        p = new ProgrammationEvenement1J(date, debut, titre, desc, duree);
    else if(type == 1)
        p = new ProgrammationRdv(date, debut, titre, desc, duree, lieu, pers);
    else if(type == 2)
        p = new ProgrammationTacheUnitaire(date, debut, *tache, *projet);
    else if(type == 3)
        p = new ProgrammationPartieTache(date, debut, *tache, num_partie, nom_partie, duree, *projet);

    verifProgrammation(p);
    if(set_prog.insert(p).second == false)
    {
        delete p;
        for(Agenda::Iterator it = begin(); it != end(); ++it)
            std::cout << "***   " << (*it).getTitre().toStdString() << " / " << (*it).getDate().toString().toStdString() << std::endl;
        throw CalendarException("Une programmation existe à cette heure");
    }
    //indique à la tache qu'elle a été programmée
    if(type == 2 || type == 3)
        tache->setIsProgrammed(true);
    notifier();
}


void Agenda::enleverProgrammation(Programmation* prog)
{
    std::vector<Programmation*> vec;
    //si la programmation a supprimer est une tache
    if(prog->type() == 2 || prog->type() == 3)
    {
        ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(prog);
        //on met le isProgrammed de la tache à false
        ptu->getTache()->setIsProgrammed(false);
        TacheUnitaire* t = ptu->getTache();
        //on parcourt toutes les autres programmations pour le cas ou ils y a des programmations de parties de taches
        //dans ce cas, on les supprimes toutes
        for(Agenda::Iterator it = begin(); it != end(); ++it)
        {
            if((*it).type() == 2 || (*it).type() == 3)
            {
                ProgrammationTacheUnitaire* tmp = dynamic_cast<ProgrammationTacheUnitaire*>(&*it);
                //si d'autres programmations possède la même tache, on l'ajout au vector vec
                if(tmp->getTache() == t)
                {
                    vec.push_back(&*it);
                }
            }
        }
    }
    //on ajoute la tache que si il est vide (évite d'ajouter 2 fois la même programmations
    if(vec.size() == 0)
        vec.push_back(prog);
    //on supprime toutes les programmations du vecteur
    for(unsigned int i = 0; i < vec.size(); ++i)
    {
        set_prog.erase(vec.at(i));
    }
    //on met à jour la vue
    notifier();
}


void Agenda::save(const QString &f, bool contraintes) const
{
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("programmations");
    //parcourt les programmations de l'agenda
    for(Agenda::ConstIterator it = begin(); it != end(); ++it){
        //si contrainte : pour l'export des programmations d'une semaine
        if(contraintes)
        {
            if((*it).getDate() >= scenes.at(0)->getDate() && (*it).getDate() <= scenes.at(6)->getDate())
            {
                (*it).exportXml(stream);
            }
        }
        //sinon pour la sauvegarde des données
        else
        {
            (*it).exportXml(stream);
        }
    }
    stream.writeEndDocument();
    newfile.close();
}


void Agenda::load(const QString &f)
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
            if(xml.name() == "programmations") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "programmation") {
                QString type;

                QDate date;
                QTime debut;
                QString titre;
                QString description;
                QDate datefin;
                QTime fin;
                Duree duree;
                QString tache;
                QString projet;
                QString numero;
                QString nom_partie;
                QString lieu;
                QString participants;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("type")) {
                    type = attributes.value("type").toString();
                }


                xml.readNext();               //xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "programmation")) {
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
                        if(xml.name() == "date") {
                            xml.readNext();
                            date=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "datefin") {
                            xml.readNext();
                            datefin=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        if(xml.name() == "debut") {
                            xml.readNext();
                            debut=QTime::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        if(xml.name() == "fin") {
                            xml.readNext();
                            fin=QTime::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        if(xml.name() == "duree") {
                            xml.readNext();
                            duree.setDuree(xml.text().toString().toUInt());
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                        if(xml.name() == "lieu") {
                            xml.readNext(); lieu=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "participants") {
                            xml.readNext(); participants=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "nom") {
                            xml.readNext(); nom_partie=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "tache") {
                            xml.readNext(); tache=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "projet") {
                            xml.readNext(); projet=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }

                        if(xml.name() == "numero") {
                            xml.readNext(); numero=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                int cas = type.toInt();
                switch(cas)
                {
                case 0:
                    ajouterProgrammation(cas, date, titre, description, debut, duree);
                    break;
                case 1:
                    ajouterProgrammation(cas, date, titre, description, debut, duree, lieu, participants);
                    break;
                case 2:
                {
                    Projet* p = ProjetManager::getInstance().getProjet(projet);
                    Tache* t = p->getTache(tache);
                    TacheUnitaire* tu = dynamic_cast<TacheUnitaire*>(t);
                    ajouterProgrammation(cas, date, "", "", debut, Duree(0), "", "", tu, p);
                    break;
                }
                case 3:
                {
                    Projet* p = ProjetManager::getInstance().getProjet(projet);
                    Tache* t = p->getTache(tache);
                    TacheUnitaire* tu = dynamic_cast<TacheUnitaire*>(t);
                    ajouterProgrammation(cas, date, "", "", debut, duree, "", "", tu, p, numero.toInt(), nom_partie);
                    break;
                }
                case 4:
                    ajouterProgrammationPlsJour(date, titre, description, debut, datefin, fin);
                    break;
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



