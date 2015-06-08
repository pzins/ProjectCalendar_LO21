#include "tache.h"



const QString Tache::info() const
{
    QString str = "<table border='0' align='center'>";
    str += "<tr><td><b>Titre</b></td><td>"+titre+"</td></tr>";
    str += "<tr><td><b>Description</b></td><td>"+description+"</td></tr>";
    str += "<tr><td><b>Disponibilité</b></td><td>"+dispo.toString()+"</td></tr>";
    str += "<tr><td><b>Echéance</b></td><td>"+echeance.toString()+"</td></tr>";
    return str;
}

bool Tache::operator==(const Tache& t)
{
    return titre == t.getTitre();
}

