#include "tache.h"



QTextStream& operator<<(QTextStream& fout, const Tache& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDuree()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";
    return fout;
}
