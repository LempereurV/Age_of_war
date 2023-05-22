#include <string>
#include <iostream>
using namespace std;

#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
using namespace Imagine;

#include "Interface.h"



void displayMenu(int epoque, int windowWidth, int windowHeight) { // affiche la barre des choix
    // loading the menu w/ the picture menu2.png
    int W, H;
    byte *r,*g,*b;
    loadColorImage(srcPath("menu2.png"), r, g, b, W, H);

    // afficher l'image
    putColorImage(windowWidth-W, 0, r, g, b, W, H);

    // delete
    delete[] r;
    delete[] g;
    delete[] b;
}

void displayMenuCharacter(){

}

void getSize(const string& filePath, int& width, int& height) { // récupérer la taille d'une image (par un moyen lourd mais pas vraiment trouvé mieux)
    byte *r,*g,*b;
    loadColorImage(filePath, r, g, b, width, height);
    delete[] r;
    delete[] g;
    delete[] b;
}

void processClickAction(int x, int y, int epoque, int windowWidth, int windowHeight) {
    int pos_x_menu = 0, pos_y_menu = 0, W_menu, H_menu; getSize(srcPath("menu2.png"), W_menu, H_menu); // récupérer la taille du menu
    if (x>pos_x_menu && x<pos_x_menu+W_menu && y>pos_y_menu && y<pos_y_menu+H_menu) {
        getActionMenu(x-pos_x_menu, y-pos_y_menu, epoque);
    }
}

void getActionMenu(int x, int y, int &epoque) { // effectue les actions du menu
    if (y>0 and y<1000){
        if (x<0 and x>1000){
            displayMenuCharacter();
        }
        if (x<0 and x>1000){
            epoque+=1;
        }
        if (x<0 and x>1000){
            drawString(100, 100, "Pas de spécial débloqué...");
        }
    }
}
