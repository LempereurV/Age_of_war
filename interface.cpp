#include <fstream>
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


bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}


void displayBase(base base1, base base2) { // affiche la base en fonction du camp
    Image<AlphaColor> basePic;
    int width, height;

    // Affichage de la base ennemie (donc renversée verticalement)
    getSize(srcPath("ennemi_base" + to_string(base2.epoque) + ".png"), width, height);
    load(basePic, srcPath("ennemi_base" + to_string(base2.epoque) + ".png"));
    display(basePic, base2.x0, 450-height);

    // Affichage de la base alliée
    getSize(srcPath("redim_base" + to_string(base1.epoque) + ".png"), width, height); // récupérer la taille du menu
    load(basePic, srcPath("redim_base" + to_string(base1.epoque) + ".png"));
    display(basePic, base1.x0-width, 450-height);
}


void afficherBackground(Window& window, int& width, int& height, int index, bool affiche) { // affiche le background des Ponts
    getSize(srcPath("backgroundPonts0.png"), width, height); // récupérer la taille du menu
    if (affiche){window = openWindow(width, height);}
    displayPicture(srcPath("backgroundPonts" + to_string(index) + ".png"), true, width, height, 0, 282*index);
}


// allié : (111, 99) // ennemi : (928, 121)
void eraseVie(int _camp_){
    int width, height;getSize(srcPath("backgroundPonts0.png"), width, height); // récupérer la taille du menu
    displayPicture(srcPath("backgroundPonts" + to_string(2+_camp_) + ".png"), true, width, height, 111+817*_camp_, 99+22*_camp_);
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


// Position initiale : allié (200, 440) // ennemi (700, 440)
void displayPers(int index, int x, int y, int camp) { // affiche le personnage d'indice index (pers_index)
    int width, height;getSize(srcPath("pers" + to_string(index) + ".png"), width, height); // récupérer la taille du menu
    Image<AlphaColor> persPic;
    if (camp == 0){
        load(persPic, srcPath("pers" + to_string(index) + ".png")); // allié
    } else {
        load(persPic, srcPath("adv_pers" + to_string(index) + ".png")); // ennemi
    }
    display(persPic, x, y-height);
}

void displaySoldiers(vector<pratique> armee, int time, int camp) {
    pratique _soldat_ ;
    for (int i=0; i<int(armee.size()); i++) {
        _soldat_ = armee.at(i) ;
        if (time > _soldat_.get_time_pop()){
            // le soldat est chargé :
            displayPers(_soldat_.get_index(), _soldat_.get_x(), 440, camp) ;
            if (camp == 0){displayBarreChargement(_soldat_, time, false);} // l'ennemi n'a pas sa barre de chargement
        } else if (camp == 0){ // le soldat n'est pas chargé :
            displayBarreChargement(_soldat_, time, true); // l'ennemi n'a oas sa barre de chargement
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
    eraseVie(0);
    drawString(barre[0][0]+barre[0][2]+5, barre[0][1]+15, to_string(base1.viemax - base1.degats), RED);

    // Base ennemie
    drop = int((barre[1][3]-2) * base2.degats / float(base2.viemax)); // drop grisé dans la barre de vie
    fillRect(barre[1][0], barre[1][1], barre[1][2], barre[1][3], BLACK);
    fillRect(barre[1][0]+1, barre[1][1]+drop+1, barre[1][2]-2, barre[1][3]-drop-2, RED);
    eraseVie(1);
    drawString(barre[1][0]+barre[1][2]+5, barre[1][1]+15, to_string(base2.viemax - base2.degats), RED);
}


void displayExp(base base1) {
    int width, height;getSize(srcPath("backgroundPonts0.png"), width, height); // récupérer la taille du menu
    displayPicture(srcPath("backgroundPonts5.png"), true, width, height, 130, 9);
    drawString(80, 40, "Exp : " + to_string(base1.exp), RED);
}


/* =========================================================================================================================================== */

void getActionMenu(int& x, int& y, int& etat, int time,
                   vector<pratique>& armee1, base& base1, base& base2, /* armée et base */
                   int& nbSpecial, int& initialize, bool& test_initialize,
                   int windowWidth, int windowHeight, Window& window) { // effectue les actions du menu

    // afficher l'univers de jeu
    afficherBackground(window, windowWidth, windowHeight, 1, false);
    displayBase(base1, base2);

    // actualiser les informations
    /* etats possibles et prévus :
         • 0: initial
         • 1: menu des personnages
    */

    if (etat == 0 and (y>29 and y<78)){
        if (x>855 and x<902){ // display menu character
            displayMenuCharac(base1.epoque, windowWidth, windowHeight);
            etat = 1;
        }
        else if (x>910 and x<956 and base1.test_epoque()){ // Changement d'époque
            if (base1.epoque==4){ // les valeurs des époques sont dans [0,5[
                drawString(windowWidth/2, windowHeight/2, "Epoque maximale atteinte", RED);
                test_initialize = true; initialize = 0; // efface avec un retard
            } else {
                afficherBackground(window, windowWidth, windowHeight, 1, false);
                displayMenu(windowWidth);
                base1.update_viemax(base1.epoque+=1);
                displayBase(base1, base2);
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

    else if (etat == 1 and (y>29 and y<78)) {
        pratique _soldat_;
        if (x>837 and x<881)
            _soldat_.initialize(3*base1.epoque, 0, armee1, time);
        else if (x>889 and x<939)
            _soldat_.initialize(3*base1.epoque+1, 0, armee1, time);
        else if (x>942 and x<989)
            _soldat_.initialize(3*base1.epoque+2, 0, armee1, time);
        else if (x>992 && x<1027 && y>29 && y<62) { // display general menu
            etat = 0;
            displayMenu(windowWidth);
        }
    }

    x=0; y=0;
}


