   /*
   Ce projet a été réalisé par                               :
                      ↪ Vianney De Monicault ↩
                        ♣ Mathieu Carrière ♣

   dans le cadre de l'Atelier de Programmation supervisé par :
                       ⊛✻⊛ Pascal Monasse ⊛✻⊛

   Objet : Réalisation d'une adaptation du jeu "Age of War,
   a game by Louissi" au thème des Ponts et à hauteur des compétences engagées.
   */




#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include "adversaire.h"
#include "Interface.h"
#include "pratique.h"
#include "theorique.h"

/* ================================================= FONCTIONS GÉNÉRALES ======================================================= */

// Fonction de saisie de souris non bloquante
bool getMouseNonBlocking(Window W, int& x, int& y) {
    Event e;
    getEvent(0, e); // Obtient un événement sans attendre

    if (e.type == EVT_NONE) { // Aucun événement
        return false;
    } else if (e.type == EVT_BUT_ON || e.type == EVT_MOTION) { // Bouton enfoncé ou mouvement
        if (e.win == W) { // Événement dans la fenêtre spécifiée
            x = e.pix[0];
            y = e.pix[1];
            return true;
        }
    }
    return false; // Ignorer les autres types d'événements ou événements hors de la fenêtre
}


// Chargement des informations du clic dans une autre variable
void refresh(int z, int& Z){if(z!=0){Z=z;}}


// Rechargement occasionnel du fond
void background(Window window, int W, int H, base base1, base base2, int& initialize, bool& test_initialize) {
    if (initialize*test_initialize >= 5){
        afficherBackground(window, W, H, 0, false);
        displayMenu(W);                  // affichage du menu
        displayBase(base1, base2);      // affichage de la base alliée
        displayBaseHealth(base1, base2); // affiche les bases
        displayEmptyBarre();
        test_initialize = false;
    }
    initialize++;
}


/* =================================================== FONCTIONS MAIN ========================================================== */

int main(){
    Window window;
    int W, H;
    afficherBackground(window, W, H, 0, true);

    // init
    int etat=0;
    vector<pratique> armee1;
    vector<pratique> armee2;
    // int argent[2]={175,175};
    base base1; base1.init(0);
    base base2; base2.init(1);

    // initialise l'adversaire
    int steps[4]; pratique _soldat_;
    ageSteps(steps);                        // Création des staps de changement d'époque
    _soldat_.initialize(0, 1, armee2, 3.);  // Initialisation du jeu de l'adversaire
    for (int i=0; i<10; i++){
        //_soldat_.initialize(0, 1, armee2, 4+3*i);
    }

    // First display
    //initializeVisuals(W, epoque1, epoque2, base1, base2, initialize, test_initialize);
    displayMenu(W);                  // affichage du menu
    displayBase(base1, base2);       // affichage de la base alliée
    displayBaseHealth(base1, base2); // affiche les bases
    displayEmptyBarre();             // affiche la barre de chargement de personnages

    // game
    //base1.exp = 1000000; // A RETIRER
    double n = 0; // variable incrémentale de temps
    int nbSpecial = 1;
    int X, Y, clicX, clicY;
    int initialize=0; bool test_initialize=false;
    while (!victoire(base1, base2)) {

        // Affichages incrémentaux
        background(window, W, H, base1, base2, initialize, test_initialize);
        displaySoldiers(armee1, n, 0);
        displaySoldiers(armee2, n, 1);
        displayBaseHealth(base1, base2);
        displayExp(base1);
        getActionMenu(X, Y, etat, n, armee1, base1, base2, nbSpecial, initialize, test_initialize, W, H, window);
        moveSoldiers(armee1, armee2, base1, base2, n);

        // Calculs incrémentaux
        ageChange(base1, base2, steps); // testé
        //cout << "updateOppArmy" << endl;
        //updateOppArmy(base1, base2, armee2, steps, n);
        updateOppArmy(base2, armee2, n);

        // Verifications itératives
        getMouseNonBlocking(window, X, Y);
        refresh(X, clicX); refresh(Y, clicY);
        drawCircle(clicX, clicY, 3, RED);

        // Decompte
        n+= 0.3;
        milliSleep(50);

        cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;
    }

    // Fin du jeu
    cout<<WhoWins(base1, base2)<<endl;
    if (WhoWins(base1, base2))
        drawString(480, 250, "Defaite", RED);
    else
        drawString(480, 250, "Victoire", RED);

    milliSleep(5000);
    endGraphics();
    return 0;
}


/* ==================================================== ZONE EXPÉRMIENTALE ===================================================== */

/*
int main(){
    for (int i=0; i<10000; i++)
        cout<<lognormalDistribution()<<endl;
    return 0;
}
*/

/*
int main(){
    int steps[4];
    srand(time(NULL)); ageSteps(steps); ageSteps(steps); // pour avoir plus de variété...
    base base1;
    base base2;
    //for (int i=0; i<500; i++){
    //    base1.exp+=1000;
    //    cout << base1.exp << " " << base1.epoque << " " << base2.exp << " " << base2.epoque << endl;
    //    ageChange(base1, base2, steps);
    //}
    for (int i=0; i<4; i++){
        cout << steps[i] << " - ";
    }
    cout << endl;
    //for (int i=0; i<4; i++){
    //    cout << _exp_[i] << " - ";
    //}
    //cout << endl;
    for (int i=0; i<1; i++){
        base1.exp = rand()%100000;
        cout << base1.exp  << " " << selec_i(base1, steps) << endl;
    }
}
*/

/*
const int freqDisplay = 100;
float start = static_cast<float>(std::time(nullptr)); // constante globale de l'heure de début


int main(){
    vector<pratique> armee1;
    vector<pratique> armee2;
    int epoque=0;
    int argent[2]={175,175};
    base base1;
    base base2;
    base1.exp=0;
    base2.exp=0;
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        // ******** Display ************ //
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            affichage(epoque);
            avancer(armee1,armee2);
            for (auto it = armee1.begin(); it != armee1.end(); ++it) {
                (*it).attaquer(armee2[0]);
            }
            for (auto it = armee2.begin(); it != armee2.end(); ++it){
                (*it).attaquer(armee1[0]);
            }
            armee1[0].refresh(armee1,armee2,argent,base1,base2);
            armee2[0].refresh(armee1,armee2,argent,base1,base2);
            noRefreshEnd();
            milliSleep(50);
        }
    }}
*/
