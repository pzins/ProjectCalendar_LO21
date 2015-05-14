#include "programmationevenement1j.h"

void ProgrammationEvenement1J::afficher() const
{
    std::cout << "date : " << getDate().toString().toStdString() << std::endl;
    std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
    std::cout << "titre : " << getTitre().toStdString() << std::endl;
    std::cout << "description : " << getDescription().toStdString() << std::endl;
    QTextStream a(stdout);
    duree.afficher(a);
}
