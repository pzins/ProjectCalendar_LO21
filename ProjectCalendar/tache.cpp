#include "tache.h"



QTextStream& operator<<(QTextStream& fout, const Tache& t){
    //fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    //fout<<t.getDuree()<<"\n";
    fout<<t.getDispo().toString()<<"\n";
    fout<<t.getEcheance().toString()<<"\n";
    return fout;
}
