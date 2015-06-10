#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDirModel>
#include <QStandardItemModel>

#include "agenda.h"
#include "dialogprecedence.h"

namespace Ui {
class MainWindow;
}

/**
 * @class MainWindow
 * @brief fenêtre principale
 */
class MainWindow : public QMainWindow, public Observateur
{
    Q_OBJECT

private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow& operator=(const MainWindow& m);
    MainWindow(const MainWindow& m);

    Ui::MainWindow *ui;
    static MainWindow* instance;

    ProjetManager* pm;
    PrecedenceManager* pre;
    Agenda* ag;


public:
    static MainWindow& getInstance(QWidget* parent = 0);
    static void libererInstance();


    virtual void update(const QString& s1="", const QString& s2="");

    /**
     * @brief supprimerProgrammation : suppression de programmation
     * @param v QGraphicsView
     */
    void supprimerProgrammation(QGraphicsView& v);

    /**
     * @brief getInformation : affiche les informations des programmations
     * @param v QGraphicsView
     */
    void getInformation(QGraphicsView& v);

    /**
     * @brief initCalendar : initialise le calendrier
     * @param d date
     */
    void initCalendar(QDate d);

    /**
      * @brief closeEvent : ferme l'application et libère l'instance de MainWindow qui
      * va elle libérer les instance de Agenda, ProjetManager et PrecedenceManager
      * @param event
      */
     void closeEvent(QCloseEvent* event){
         libererInstance();
     }

public slots:
     /**
     * @brief adaptForm adapte le formulaire en fonction des choix fait par l'utilisateur
     * @param etat
     */
    void adaptForm(bool etat);

    /**
    * @brief adaptForm2 adapte le formulaire en fonction des choix fait par l'utilisateur
     * @param etat
     */
    void adaptForm2(bool etat);

    /**
     * @brief expand : étend l'affichage du TreeView
     */
    void expand();

    /**
     * @brief sauvegarder : lance la sauvegarde des données
     */
    void sauvegarder();

    /**
     * @brief charger : charge les données
     */
    void charger();

    /**
     * @brief ajouter : fait des vérifications et si il n'y a pas de problème
     * l'ajout du projet ou de la tache sera effectué
     */
    void ajouter();

    /**
     * @brief supprimerItem : suppression d'un item dans le TreeView
     * cela entrainera la suppression réelle de l'item (tache ou projet)
     */
    void supprimerItem();

    /**
     * @brief afficherInfo : affiche l'information d'un item (tache ou projet) selectionné dans le TreeView
     * @param idx
     */
    void afficherInfo(QModelIndex idx);

    /**
     * @brief ajouterPrecedence : lance la fenetre de dialogue pour l'ajout de contraintes de precedences
     */
    void ajouterPrecedence();

    /**
     * @brief supprimerPrecedence : suppression d'un item de la QList ce qui entrainera la suppression réelle de
     * la précédence
     */
    void supprimerPrecedence();

    /**
     * @brief programmerTache : lance la fenetre de dialogue concernant l'ajout de programmations de tache
     */
    void programmerTache();

    /**
     * @brief ajouterEvt : lance la fenetre de dialogue concernant l'ajout de programmation d'événement traditionnels
     */
    void ajouterEvt();

    /**
     * @brief changeDate : va mettre à jour les vues de chaque jours pour afficher la bonne semain
     */
    void changeDate();

    //SLOT déclenchés lors du clic dans une des 7 vues
    //cela affichera les informations de la programmation ou supprimer la programmation
    void lundi();
    void mardi();
    void mercredi();
    void jeudi();
    void vendredi();
    void samedi();
    void dimanche();

    /**
     * @brief exporterSemaine : exportera toutes les programmations d'une semaine en fichier XML
     */
    void exporterSemaine();

};




#endif // MAINWINDOW_H
