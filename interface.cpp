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

void afficherBackground(Window& window, int& width, int& height, int index, bool affiche) { // affiche le background des Ponts
    getSize(srcPath("backgroundPonts0.png"), width, height); // récupérer la taille du menu
    if (affiche){window = openWindow(width, height);}
    displayPicture(srcPath("backgroundPonts" + to_string(index) + ".png"), true, width, height, 0, 282*index);
}

int barrePerso[4] = {200, 25, 500, 20};
void displayEmptyBarre() {
    fillRect(barrePerso[0], barrePerso[1], barrePerso[2], barrePerso[3], BLACK);
}

void displayBarreChargement(pratique _soldat_, int time, bool formation) {
    // affiche la barre de chargement du soldat en cours de formation
    if (formation) {
        // selection initiale à t_selection = time_fin - duree_formation
        // durée passée à la formation = time - t_selection = time - time_fin + duree_formation
        // longueur = barrePerso[2] * (time - time_fin + duree_formation) / duree_formation
        float alpha = (time-_soldat_.get_time_pop())/_soldat_.get_duree_formation();
        fillRect(barrePerso[0]+1, barrePerso[1]+1, barrePerso[2]*(1+alpha)-2, barrePerso[3]-2, RED);
    } else {
        displayEmptyBarre();
    }
}

void displaySoldiers(vector<pratique> armee, int time) {
    pratique _soldat_ ;
    for (int i=0; i<int(armee.size()); i++) {
        _soldat_ = armee.at(i) ;
        if (time > _soldat_.get_time_pop()){
            // le soldat est chargé :
            displayPers(_soldat_.get_index(), _soldat_.get_x(), 440) ;
            displayBarreChargement(_soldat_, time, false);
        } else {
            // le soldat n'est pas chargé :
            displayBarreChargement(_soldat_, time, true);
        }
    }
}

int barre[2][4] = {{100, 135, 10, 125},
                   {920, 135, 10, 125}};

void displayBaseHealth(base base1, base base2) {
    // Base alliée
    int drop = int((barre[0][3]-2) * base1.degats / float(base1.viemax)); // drop grisé dans la barre de vie
    fillRect(barre[0][0], barre[0][1], barre[0][2], barre[0][3], BLACK);
    fillRect(barre[0][0]+1, barre[0][1]+drop+1, barre[0][2]-2, barre[0][3]-drop-2, RED);
    drawString(barre[0][0]+barre[0][2]+5, barre[0][1]+15, to_string(base1.viemax - base1.degats), RED);

    // Base ennemie
    drop = int((barre[1][3]-2) * base2.degats / float(base2.viemax)); // drop grisé dans la barre de vie
    fillRect(barre[1][0], barre[1][1], barre[1][2], barre[1][3], BLACK);
    fillRect(barre[1][0]+1, barre[1][1]+drop+1, barre[1][2]-2, barre[1][3]-drop-2, RED);
    drawString(barre[1][0]+barre[1][2]+5, barre[1][1]+15, to_string(base2.viemax - base2.degats), RED);
}

/* =============================================== ~~~~~ ♥♥ INITIALIZER ♥♥ ~~~~~ ============================================================== */
/*void initializeVisuals(int W, int epoque1, int epoque2, base base1, base base2, int& initialize, bool& test_initialize) {
    //std::cout << "in_initializeVisuals" << std::endl;
    if (initialize*test_initialize >= 5){
        //std::cout << "in_if_initializeVisuals" << std::endl;
        displayMenu(W);                  // affichage du menu
        displayBase(epoque1, epoque2);   // affichage des bases
        displayBaseHealth(base1, base2); // affiche les bases
        displayEmptyBarre();             // affiche la barre de chargement de personnages
        test_initialize = false;
    }
    //std::cout << "in_initializeVisuals_2" << std::endl;
    initialize++;
    //std::cout << "out_initializeVisuals" << std::endl;
}*/

/* =========================================================================================================================================== */

void getActionMenu(int& x, int& y, int& epoque, int& etat, int time,
                   vector<pratique>& armee1, base& base1, /* armée et base */
                   int& nbSpecial, int& initialize, bool& test_initialize,
                   int windowWidth, int windowHeight, Window& window) { // effectue les actions du menu
    // afficher l'univers de jeu
    afficherBackground(window, windowWidth, windowHeight, 1, false);
    displayBase(epoque, 0);

    // actualiser les informations
    /* etats possibles et prévus :
         • 0: initial
         • 1: menu des personnages
    */
    if (etat == 0){
        //displayMenu(windowWidth);
        if (y>29 and y<78){
            if (x>855 and x<902){ // display menu character
                etat = 1;
                displayMenuCharac(epoque, windowWidth, windowHeight);
            }
            else if (x>910 and x<956 and base1.test_epoque()){ // Changement d'époque
                if (epoque==4){ // les valeurs des époques sont dans [0,5[
                    drawString(windowWidth/2, windowHeight/2, "Epoque maximale atteinte", RED);
                    test_initialize = true; initialize = 0; // efface avec un retard
                } else {
                    afficherBackground(window, windowWidth, windowHeight, 1, false);
                    displayMenu(windowWidth);
                    displayBase(epoque+=1, 0);
                    base1.update_viemax(epoque);
                    nbSpecial = 1;
                }
            }
            else if (x>963 and x<1010){
                if (nbSpecial == 1){
                    // Fonction spécial
                    nbSpecial = 0;
                } else {
                    drawString(windowWidth/2, windowHeight/2, "Pas de spécial débloqué...", RED);
                    test_initialize = true; initialize = 0; // efface avec un retard
                }
            }
        }
    } else if (etat == 1) { //     void créer(int index, int _camp_, vector<pratique> armee1, vector<pratique> armee2);
        //displayMenuCharac(epoque, windowWidth, windowHeight);
        if (y>29 and y<78){
            pratique _soldat_;
            if (x>837 and x<881)
                _soldat_.initialize(3*epoque, 0, armee1, time);
            else if (x>889 and x<939)
                _soldat_.initialize(3*epoque+1, 0, armee1, time);
            else if (x>942 and x<989)
                _soldat_.initialize(3*epoque+2, 0, armee1, time);
            else if (x>992 && x<1027 && y>29 && y<62) { // display general menu
                etat = 0;
                displayMenu(windowWidth);
            }
        }
    }
    x=0; y=0;
}


