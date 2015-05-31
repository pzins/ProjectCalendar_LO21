#include "tache.h"



QTextStream& operator<<(QTextStream& fout, const Tache& t){
    //fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    //fout<<t.getDuree()<<"\n";
    fout<<t.getDispo().toString()<<"\n";
    fout<<t.getEcheance().toString()<<"\n";
    return fout;
}
QString Tache::info() const
{
    QString str = "<table border='0' align='center'>";
    str += "<tr><td><b>Titre</b><td >"+titre+"</td></td></tr>";
    str += "<tr><td><b>Description</b><td >"+description+"</td></td></tr>";
    str += "<tr><td><b>Disponibilité</b><td >"+dispo.toString()+"</td></td></tr>";
    str += "<tr><td><b>Echéance</b><td >"+echeance.toString()+"</td></td></tr>";
    return str;
}

