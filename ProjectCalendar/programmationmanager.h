#ifndef PROGRAMMATIONMANAGER_H
#define PROGRAMMATIONMANAGER_H
#include "programmation.h"


class ProgrammationManager {
private:
    std::vector<Programmation*> vect_progr;
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;
public:
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager& um);
    ProgrammationManager& operator=(const ProgrammationManager& um);
    void ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h);
};

#endif // PROGRAMMATIONMANAGER_H
