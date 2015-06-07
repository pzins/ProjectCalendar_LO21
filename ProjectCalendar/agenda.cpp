#include "agenda.h"
#include "jourscene.h"
#include "programmation.h"
#include "programmationrdv.h"
#include "programmationtacheunitaire.h"
#include "programmationpartietache.h"
#include "projetmanager.h"

Agenda* Agenda::instance = 0;



void Agenda::ajouterScene(const QString& jour, const QDate& date, qreal h, qreal w, QObject *parent)
{
    JourScene* js = new JourScene(jour,date,0,0,w-2,h-2,840,parent);
    ajouterObservateur(js);
    scenes.push_back(js);
}



Agenda::~Agenda(){
    //for(unsigned int i=0; i<vect_progr.size(); i++) delete vect_progr[i];
   /* for(Agenda::Iterator it = vect_progr.begin(); it != vect_progr.end(); ++it)
        delete *it;*/
}

void Agenda::notifier(const QString& s1, const QString& s2)
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
    try
    {
        verifProgrammation(p);
        if(set_prog.insert(p).second == false)
        {
            delete p;
            throw CalendarException("Erreur, Agenda, une programmation existe à cette heure");
        }
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
    notifier();
}



void Agenda::verifProgrammation(Programmation* p)
{
    for(std::set<Programmation*, ProgComp>::iterator it = set_prog.begin(); it != set_prog.end(); ++it)
    {
      if(p->isEvtPlsJ())
        {
            ProgrammationEvenementplsJ* tmp = dynamic_cast<ProgrammationEvenementplsJ*>(p);
            if(tmp->getDate() == (*it)->getDate())
            {
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > tmp->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
            else if (tmp->getDateFin() == (*it)->getDate())
            {
                if(tmp->getFin() > (*it)->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
            else if(tmp->getDate() < (*it)->getDate() && tmp->getDateFin() > (*it)->getDate())
            {
                throw CalendarException("Erreur, Agenda, chevauchement de programmation");
            }

        }
        else
        {
            if(p->getDate() == (*it)->getDate() && (*it)->getDebut() < p->getDebut())
            {
                QTime fin = (*it)->getDebut().addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
                if(fin > p->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
            else if(p->getDate() == (*it)->getDate() && (*it)->getDebut() > p->getDebut())
            {
                QTime fin = p->getDebut().addSecs(p->getDuree().getDureeEnMinutes() * 60);
                if(fin > (*it)->getDebut())
                {
                    throw CalendarException("Erreur, Agenda, chevauchement de programmation");
                }
            }
        }
    }
}

void Agenda::ajouterProgrammationPartieTache(std::vector<QDate>& vec_date, std::vector<QString>& vec_titre,
                                             std::vector<QTime>& vec_debut, std::vector<Duree>& vec_duree,
                                             TacheUnitaire* t, const QString& projet)
{
    std::vector<ProgrammationPartieTache*> vec;
    try
    {

        for(int i = 0; i < vec_date.size(); ++i)
        {
            vec.push_back(new ProgrammationPartieTache(vec_date.at(i), vec_debut.at(i), *t, i+1,
                                                   vec_titre.at(i), vec_duree.at(i), projet));
            verifProgrammation(vec.at(i));
        }
        for(int i = 0; i < vec.size(); ++i)
        {
            set_prog.insert(vec.at(i));
        }
        vec.at(0)->getTache()->setIsProgrammed(true);
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;

        for(int i = 0; i < vec.size(); ++i)
        {
            delete vec.at(i);
        }
    }
    notifier();
}


void Agenda::ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                  const Duree& duree, const QString& lieu, const QString& pers, TacheUnitaire* tache,
                                  const QString& projet, int num_partie, const QString nom_partie)
{
    Programmation* p;
    if(type == 0)
        p = new ProgrammationEvenement1J(date, debut, titre, desc, duree);
    else if(type == 1)
        p = new ProgrammationRdv(date, debut, titre, desc, duree, lieu, pers);
    else if(type == 2)
        p = new ProgrammationTacheUnitaire(date, debut, *tache, projet);
    else if(type == 3)
        p = new ProgrammationPartieTache(date, debut, *tache, num_partie, nom_partie, duree, projet);
    try
    {
        verifProgrammation(p);
        if(set_prog.insert(p).second == false)
        {
            delete p;
            throw CalendarException("Erreur, Agenda, une programmation existe à cette heure");
        }
        if(type == 2 || type == 3)
            tache->setIsProgrammed(true);
    }
    catch(CalendarException e)
    {
        std::cout << e.getInfo().toStdString() << std::endl;
    }
    notifier();
}

void Agenda::enleverProgrammation(Programmation* prog)
{
    if(prog->isTache())
    {
        ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(prog);
        ptu->getTache()->setIsProgrammed(false);
    }
    if(set_prog.erase(prog) == 0)
        throw CalendarException("Erreur, Agenda, cet Programmation n'existe pas");
    notifier();
}


void Agenda::save(const QString &f, bool contraintes)
{
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("programmations");
    for(Agenda::Iterator it = begin(); it != end(); ++it){
        if(contraintes)
        {
            if((*it).getDate() >= scenes.at(0)->getDate() && (*it).getDate() <= scenes.at(6)->getDate())
            {
                (*it).exportXml(stream);
            }
        }
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
                    ajouterProgrammation(cas, date, "", "", debut, Duree(0), "", "", tu);
                    break;
                }
                case 3:
                {
                    Projet* p = ProjetManager::getInstance().getProjet(projet);
                    Tache* t = p->getTache(tache);
                    TacheUnitaire* tu = dynamic_cast<TacheUnitaire*>(t);
                    ajouterProgrammation(cas, date, "", "", debut, duree, "", "", tu, projet, numero.toInt(), nom_partie);
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



