#include <QCoreApplication>
#include "programmationtacheunitaire.h"
#include "agenda.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    Agenda& ag = Agenda::getInstance();
    TacheUnitaire t("ol","ol", Duree(5,6), QDate(2,2,2), QDate(3,3,3));
    ProgrammationTacheUnitaire p(QDate(1,1,1), QTime(1,2), t);

    //ProgrammationTacheUnitaire p(QDate(1,1,1), QTime(1,2), *t);*/
    return a.exec();
}
