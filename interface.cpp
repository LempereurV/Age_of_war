#include <string>
#include <iostream>
using namespace std;

#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
using namespace Imagine;

#include "Interface.h"
#include "pratique.h"

/* =========================================================================================================================================== */

void displayPicture(const std::string & file, bool debut, int windowWidth, int windowHeight, int positionX, int positionY) { // affiche la barre des choix
    /* bool debut pour définir si positionX et positionY sont les ancrages à (0,0) ou (windowWidth, windowHeight) */
    // loading the picture
    int W, H;
    byte *r, *g, *b;
    loadColorImage(file, r, g, b, W, H);

    // afficher l'image
    if (debut){
        putColorImage(min(windowWidth, positionX), min(windowHeight, positionY), r, g, b, W, H);
    }else{
        putColorImage(max(windowWidth - positionX, 0), max(windowHeight - positionY, 0), r, g, b, W, H);
    }
    // delete
    delete[] r;
    delete[] g;
    delete[] b;
}

void getSize(const string& filePath, int& width, int& height) { // récupérer la taille d'une image (par un moyen lourd mais pas vraiment trouvé mieux)
    byte *r,*g,*b;
    loadColorImage(filePath, r, g, b, width, height);
    delete[] r;
    delete[] g;
    delete[] b;
}

/* =========================================================================================================================================== */

void displayMenu(int windowWidth) { // affiche la barre des choix
        // loading the menu w/ the picture menuGeneral.png
        int W, H;
        byte *r,*g,*b;
        loadColorImage(srcPath("menuGeneral.png"), r, g, b, W, H);
        // afficher l'image
        putColorImage(windowWidth-W, 0, r, g, b, W, H);
        // delete
        delete[] r;
        delete[] g;
        delete[] b;
}

void displayMenuCharac(int epoque, int windowWidth, int windowHeight) {  // affiche la barre des choix des personnages
    // loading the menu
    int W, H;
    byte *r,*g,*b;
    loadColorImage(srcPath("menuPers.png"), r, g, b, W, H);

    // afficher l'image
    putColorImage(windowWidth-W, 0, r, g, b, W, H);

    // load les trois persos AVEC CHOIX EN FONCTION DE EPOQUE
    displayPicture(srcPath("aff" + to_string(3*epoque) + ".png"), true, windowWidth, windowHeight, 835, 32);
    displayPicture(srcPath("aff" + to_string(3*epoque+1) + ".png"), true, windowWidth, windowHeight, 889, 32);
    displayPicture(srcPath("aff" + to_string(3*epoque+2) + ".png"), true, windowWidth, windowHeight, 943, 32);

    // delete
    delete[] r;
    delete[] g;
    delete[] b;
}

void displayBase(int epoque1, int epoque2) { // affiche la base en fonction du camp
    int width, height;getSize(srcPath("redim_base" + to_string(epoque1) + ".png"), width, height); // récupérer la taille du menu
    // Affichage de la base alliée
    Image<AlphaColor> basePic;
    load(basePic, srcPath("redim_base" + to_string(epoque1) + ".png"));
    display(basePic, 240-width, 450-height);

    // Affichage de la base ennemie (donc renversée verticalement)
    getSize(srcPath("redim_base" + to_string(epoque2) + ".png"), width, height);
    load(basePic, srcPath("ennemi_base" + to_string(epoque2) + ".png"));
    display(basePic, 800, 450-height);
}

// Position initiale alliée (200, 440) // ennemie (, )
void displayPers(int index, int x, int y) { // affiche le personnage d'indice index (pers_index)
    int width, height;getSize(srcPath("pers" + to_string(index) + ".png"), width, height); // récupérer la taille du menu
    Image<AlphaColor> basePic;
    load(basePic, srcPath("pers" + to_string(index) + ".png"));
    display(basePic, x, y - height);
}

void afficherBackground(int& width, int& height, bool affiche) { // affiche le background des Ponts
    getSize(srcPath("backgroundPonts.png"), width, height); // récupérer la taille du menu
    if (affiche){openWindow(width, height);}
    displayPicture(srcPath("backgroundPonts.png"), width, height, true, 0, 0);
}

/* =========================================================================================================================================== */

void getActionMenu(int x, int y, int& epoque, int& etat,
                   vector<pratique> armee1, base base1, /* armée et base */
                   int windowWidth, int windowHeight) { // effectue les actions du menu
    // afficher l'univers de jeu
    afficherBackground(windowWidth, windowHeight, false);
    displayBase(epoque, 0);
    /* actualiser les informations
       etats possibles et prévus :
         • 0: initial
         • 1: menu des personnages
    */
    if (etat == 0){
        displayMenu(windowWidth);
        if (y>29 and y<78){
            if (x>855 and x<902){ // display menu character
                etat = 1;
                displayMenuCharac(epoque, windowWidth, windowHeight);
            }
            else if (x>910 and x<956 and base1.test_epoque()){ // Changement d'époque
                if (epoque==4){ // les valeurs des époques sont dans [0,5[
                    cout<<"Epoque maximale atteinte"<<endl;
                } else {
                    afficherBackground(windowWidth, windowHeight, false);
                    displayMenu(windowWidth);
                    displayBase(epoque+=1, 0);
                }
            }
            else if (x>963 and x<1010){
                drawString(windowWidth/2, windowHeight/2, "Pas de spécial débloqué...", RED);
            }
        }
    } else if (etat == 1) {
        displayMenuCharac(epoque, windowWidth, windowHeight);
        if (y>29 and y<78){
            if (x>837 and x<881) {
                cout << "sors le soldat " << 3*epoque << endl;
                //displayPicture(srcPath("pers" + to_string(3*epoque) + ".png"), true, windowWidth, windowHeight, 110, 391);
                displayPers(3*epoque, 200, 440);
                // armee1.creer(3*epoque, 0, armee1, armee2);
            }
            else if (x>889 and x<939) {
                cout << "sors le soldat " << 3*epoque+1 << endl;
                //displayPicture(srcPath("pers" + to_string(3*epoque+1) + ".png"), true, windowWidth, windowHeight, 110, 391);
                displayPers(3*epoque+1, 200, 440);
                // armee1.creer(3*epoque+1, 0, armee1, armee2);
            }
            else if (x>942 and x<989) {
                cout << "sors le soldat " << 3*epoque+2 << endl;
                //displayPicture(srcPath("pers" + to_string(3*epoque+2) + ".png"), true, windowWidth, windowHeight, 110, 391);
                displayPers(3*epoque+2, 200, 440);
                // armee1.creer(3*epoque+2, 0, armee1, armee2);
            }
            else if (x>992 && x<1027 && y>29 && y<62) { // display general menu
                etat = 0;
                displayMenu(windowWidth);
            }
        }
    }
}


