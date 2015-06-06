#include "programmation.h"

const QString Programmation::toString() const
{
    QString str = "<tr><td><b>Date</b><td >"+date.toString()+"</td></td></tr>";
    str += "<tr><td><b>Début</b><td >"+debut.toString()+"</td></td></tr>";
    return str;
}
