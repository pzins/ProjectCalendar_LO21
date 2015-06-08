#ifndef JOURSCENE_H
#define JOURSCENE_H
#include <QGraphicsScene>
#include <QDate>
#include "duree.h"
#include "programmation.h"
#include "programmationitem.h"
#include "programmationevenementplsj.h"
#include "observateur.h"

/**
 * @struct Couleur
 * @brief Structure contenant les couleurs de fond et de contour pour une programmations dans le calendrier
 */
struct Couleur
{
    QColor contour;
    QColor fond;
};


/**
 * @class JourScene
 * @brief Scene permettant de gérer ce qui sera afficher dans nos vues pour chaque jour
 */
class JourScene : public QGraphicsScene, public Observateur
{

private:
    QString jour;
    QDate date;
    unsigned int minutes;
    Couleur vec_couleur[5];

public:
    /**
     * @brief JourScene
     * @param nom_ jour de la semaine
     * @param date_
     * @param x_ position x
     * @param y_ position y
     * @param width_ largeur
     * @param height_ hauteur
     * @param minutes_
     * @param parent
     */
    JourScene(const QString& nom_, const QDate& date_, qreal x_, qreal y_, qreal width_, qreal height_,
              unsigned int minutes_ = 840, QObject* parent = 0 )
        :  QGraphicsScene(x_,y_,width_,height_,parent),jour(nom_),date(date_), minutes(minutes_)
    {
        vec_couleur[0] = {QColor("black"),QColor("red")};
        vec_couleur[1] = {QColor("black"),QColor("orange")};
        vec_couleur[2] = {QColor("black"),QColor("lightgreen")};
        vec_couleur[3] = {QColor("black"),QColor("yellow")};
        vec_couleur[4] = {QColor("black"),QColor("lightblue")};

        dessinerFond();
    }

    const QDate& getDate() const {return date;}
    void setDate(QDate& d) {date = d;}

    /**
     * @brief ajouterProgrammation : ajoute une programmation de l'agenda à la scene
     * @param titre
     * @param debut horaire de début
     * @param duree
     * @param e programmation de l'agenda
     * @param type
     */
    void ajouterProgrammation(const QString titre, const QTime& debut, const Duree& duree,
            Programmation* e=0, int type=0);
    /**
     * @brief dessinerFond : dessiner le fond du calendrier
     */
    void dessinerFond();

    /**
     * @brief removeAllItems : vide la scene
     */
    void removeAllItems();

    /**
     * @brief update : met la scene à jour à partir de l'agenda
     * @param s1
     * @param s2
     */
    virtual void update(const QString& s1="", const QString& s2="");

};

#endif // JOURSCENE_H
