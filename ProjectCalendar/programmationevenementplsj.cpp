#include "programmationevenementplsj.h"


void ProgrammationEvenementplsJ::afficher() const
{
    std::cout << "date : " << getDate().toString().toStdString() << std::endl;
    std::cout << "debut : " << getDebut().toString().toStdString() << std::endl;
    std::cout << "titre : " << getTitre().toStdString() << std::endl;
    std::cout << "description : " << getDescription().toStdString() << std::endl;
    std::cout << "date de fin : " << date_fin.toString().toStdString() << std::endl;
    std::cout << "fin : " << fin.toString().toStdString() << std::endl;
}
