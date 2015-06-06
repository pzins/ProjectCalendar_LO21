#include "programmationevenement.h"

const QString ProgrammationEvenement::toString() const
{
    QString str = "<table border='0' align='center'>";
    str += "<tr><td><b>Titre</b><td >"+titre+"</td></td></tr>";
    str += "<tr><td><b>Description</b><td >"+description+"</td></td></tr>";
    str += Programmation::toString();
    return str;
}
