#include "tacheunitaire.h"
#include <iostream>
#include "agenda.h"



void TacheUnitaire::exportXml(QXmlStreamWriter &stream)
{
    stream.writeStartElement("tache");
    stream.writeAttribute("preemptive", isPreemptive()?"true":"false");
    stream.writeTextElement("titre", getTitre());
    stream.writeTextElement("description",getDescription());
    stream.writeTextElement("disponibilite",getDispo().toString(Qt::ISODate));
    stream.writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    QString str;
    str.setNum(duree.getDureeEnMinutes());
    stream.writeTextElement("duree",str);
    stream.writeEndElement();
}

QString TacheUnitaire::info() const
{
    QString str = "<h3 align='center'>Tache Unitaire</h3>"+Tache::info();
    str += "<tr><td><b>Durée</b></td><td >"+duree.toString()+"</td></tr>";
    if(isProgrammed())
    {
        Agenda* ag = &Agenda::getInstance();
        for(Agenda::Iterator it = ag->begin(); it != ag->end(); ++it)
        {
            if((*it).isTache())
            {
                ProgrammationTacheUnitaire* p = dynamic_cast<ProgrammationTacheUnitaire*>(&*it);
                if(p->getTache() == this)
                {
                    str += "<tr><td><b>Programmation</b></td><td>"+p->getDate().toString()+", "+p->getDebut().toString()+"</td></tr>";
                }
            }
        }
    }
    str += "</table>";

    return str;
}

TacheUnitaire::~TacheUnitaire()
{
    Agenda* ag = &Agenda::getInstance();
    std::vector<Programmation*> vec;
    for(Agenda::Iterator it = ag->begin(); it != ag->end(); ++it)
    {
        if((*it).isTache())
        {
            ProgrammationTacheUnitaire* ptu = dynamic_cast<ProgrammationTacheUnitaire*>(&(*it));
            if(ptu->getTache() == this)
            {
                vec.push_back(&*it);
            }
        }
    }
    for(std::vector<Programmation*>::iterator it = vec.begin(); it != vec.end(); ++it)
        ag->enleverProgrammation(*it);
}
