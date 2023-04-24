#include "liste.cpp"
#include "pratique.h"
#include <iostream>
#include<vector>
#include <unistd.h>
using namespace std ;

void pratique::creer(int pos, int c,vector<pratique> armee1,vector<pratique> armee2){
    int x0=0;
    if (camp==1)
        x0=100;
    pratique soldat;
    soldat.x=x0;
    soldat.vie=global[pos].viemax;
    soldat.camp=c;
    sleep(proprietes.temps);
    if(c==0){
        armee1.push_back(soldat);
    }
    else
        armee2.push_back(soldat);
};

void pratique::avancer(vector<pratique> armee1, vector<pratique> armee2){
    if(abs(armee1[0].x-armee2[0].x)<2){
        for (auto it = armee1.begin(); it != armee1.end(); ++it) {
            x+=1;
        }
        for (auto it = armee2.begin(); it != armee2.end(); ++it){
            x-=1;
        }
    }
}

void pratique::attaquer(pratique ennemi){
    if(abs(x-ennemi.x)<proprietes.portee){
        while(vie>0){
            ennemi.vie-=proprietes.force;
            sleep(proprietes.frequence/2);
        }
    }
}

void pratique::mourir(vector<pratique> armee1, vector<pratique> armee2){
    if(camp==0)
        armee1.pop_back();
    else
        armee2.pop_back();
}

void pratique::refresh(int d, int c,vector<pratique> armee1, vector<pratique> armee2){
    vie-=d;
    if (vie<0){
        if(c==0)
            armee1.pop_back();
        else
            armee2.pop_back();
    }
}






