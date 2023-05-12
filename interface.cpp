#include "Interface.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

void affichage(int epoque){ // affiche la barre des choix
    int W, H;
    byte *r,*g,*b;
    loadColorImage(srcPath("menu.png"), r, g, b, W, H);
}
