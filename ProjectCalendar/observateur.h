#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H
#include <set>
#include <QString>


/**
 * @class Observateur
 * @brief class abstraite permettant d'observer d'autres objets
 */
class Observateur
{
public:
    /**
     * @brief update : mise à jour de l'objet
     * @param s1 paramètre optionel
     * @param s2 paramètre optionel
     */
    virtual void update(const QString& s1="", const QString& s2="")=0;

};

#endif // OBSERVATEUR_H
