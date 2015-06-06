#include <iostream>
#include "programmationrdv.h"



void ProgrammationRdv::afficher() const
{
    ProgrammationEvenement1J::afficher();
    std::cout << "lieu : " << lieu.toStdString()<< std::endl;
    for(unsigned int i = 0; i < personne.size(); ++i)
    std::cout << "personne" << i << " : " << personne[i].toStdString() << std::endl;
}

const QString ProgrammationRdv::toString() const
{
    QString str = ProgrammationEvenement::toString();
    str += "<tr><td><b>Lieu</b><td >"+lieu+"</td></td></tr>";
    str += "<tr><td><b>Participants</b><td >";
    for(int i = 0; i < personne.size(); ++i)
        str += personne.at(i) +"<br>";
    str += "</td></td></tr>";
    return str;
}
