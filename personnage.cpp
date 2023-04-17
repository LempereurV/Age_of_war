#include "personnage.h"
#include <iostream>
#include "liste.cpp"

using namespace std ;


pratique pratique::creer(int pos, int camp){
    int x0=0;
    if (camp==1)
        x0=100;
    pratique soldat();
    x=x0;
    vie=viemax.global[pos];
};

std::queue<pratique> file;
