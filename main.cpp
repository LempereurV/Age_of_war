#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
using namespace std;

#include "adversaire.h"
#include "Interface.h"
#include "pratique.h"
#include "theorique.h"


const int freqDisplay = 100;

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

void refresh(int z, int& Z){if(z!=0){Z=z;}}

int main(){
    Window window;
    int W, H;
    afficherBackground(window, W, H, 0, true);

    // init
    int epoque1=0, epoque2=0, etat=0;
    vector<pratique> armee1;
    vector<pratique> armee2;
    // int argent[2]={175,175};
    base base1;
    base base2;

    // First display
    displayMenu(W);     // affichage du menu
    displayBase(epoque1, epoque2);  // affichage des bases
    displayBaseHealth(base1, base2); // affiche les bases

    // game
    base1.exp = 1000000; // A RETIRER
    double n = 0; // variable incrémentale de temps
    int X, Y, clicX, clicY;
    while (true) {
        // Verifications itératives
        getMouseNonBlocking(window, X, Y);
        refresh(X, clicX); refresh(Y, clicY);
        drawCircle(clicX, clicY, 3, RED);

        // Affichages incrémentaux
        getActionMenu(X, Y, epoque1, etat, n, armee1, base1, W, H, window);
        displayBaseHealth(base1, base2);
        displaySoldiers(armee1, armee2, n);
        moveSoldiers(armee1, armee2);

        // Decompte
        n+= 1;
        milliSleep(200);
    }
    endGraphics();
}

/*
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
