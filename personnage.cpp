#include "personnage.h"
#include <iostream>
#include "liste.cpp"
#include<vector>
using namespace std ;

vector<pratique> armee1;
vector<pratique> armee2;

void pratique::creer(int pos, int c){
    int x0=0;
    if (camp==1)
        x0=100;
    pratique soldat;
    soldat.x=x0;
    soldat.vie=global[pos].viemax;
    soldat.camp=c;
    if(c==0){
        armee1.push_back(soldat);
    }
    else
        armee2.push_back(soldat);
};
