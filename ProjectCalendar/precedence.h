#ifndef PRECEDENCE_H
#define PRECEDENCE_H
#include <QString>
#include "tache.h"

class Projet;

/**
 * @class Precedence
 * @brief Classe représentant les contraintes de précéndences
 */
class Precedence
{
    friend class PrecedenceManager;
private:
    Tache* pred;
    Tache* succ;
    Projet* projet;
    /**
     * @brief Precedence
     * @param pred_ tache antérieure
     * @param succ_ tache postérieure
     * @param projet_ projet concerné
     */
    Precedence(Tache& pred_, Tache& succ_, Projet& projet_) : pred(&pred_), succ(&succ_), projet(&projet_){}

public:
    Tache& getPred() const {return *pred;}
    Tache& getSucc() const {return *succ;}
    Projet& getProjet() const {return *projet;}

    /**
     * @brief toString : renvoie la précédence sous forme de texte
     * @return
     */
    QString toString() const;

    /**
     * @brief isInverse : vérifie si 2 précédences sont l'inverse l'une de l'autre
     * @param pred précédence
     * @return
     */
    bool isInverse(const Precedence& pred) const;

    bool operator<(const Precedence& p);
    bool operator ==(const Precedence& p);
    bool operator==(const Tache& t);
    bool operator==(const Projet& t);

};

#endif // PRECEDENCE_H
