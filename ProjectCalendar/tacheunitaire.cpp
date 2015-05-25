#include "tacheunitaire.h"
#include <iostream>

void TacheUnitaire::afficher(QStandardItem* it)
{
    QStandardItem* item = new QStandardItem(getTitre());
    it->appendRow(item);
}
