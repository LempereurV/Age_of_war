#include "pratique.h"
#include <iostream>
#include<vector>
#include <unistd.h>
using namespace std ;

bool base::test_epoque(){
    return (exp>requis[epoque]);
}

void pratique::creer(int pos, int c,vector<pratique> armee1,vector<pratique> armee2){
    int x0=0;
    if (c==1)
        x0=100;
    pratique soldat;
    soldat.proprietes=global[pos];
    soldat.x=x0;
    soldat.vie=soldat.proprietes.viemax;
    soldat.camp=c;
    sleep(soldat.proprietes.temps);
    if(c==0){
        armee1.push_back(soldat);
    }
    else
        armee2.push_back(soldat);
};

void avancer(vector<pratique> armee1, vector<pratique> armee2){
    if(armee1[0].distance(armee2[0])>1){
        for (auto it = armee1.begin(); it != armee1.end(); ++it) {
            (*it).pas(1);
        }
        for (auto it = armee2.begin(); it != armee2.end(); ++it){
            (*it).pas(-1);
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

void pratique::mourir(vector<pratique> armee1, vector<pratique> armee2,int argent[2],base base1, base base2){
    if(camp==0){
        armee1.pop_back();
        argent[1]+=proprietes.prime;
        base2.exp+=proprietes.exp;
    }
    else{
        armee2.pop_back();
        argent[0]+=proprietes.prime;
        base1.exp+=proprietes.exp;
    }
}

void pratique::refresh(int d, int c,vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2){
    vie-=d;
    if (vie<0){
        mourir(armee1, armee2, argent, base1, base2);
    }
}

bool pratique::reach(int xA,int p){
    //xA: abscisse de celui qu'on considère et p sa portée
    return(abs(x-xA)<p);
}

int pratique::distance(pratique ennemi){
    return abs(x-ennemi.x);
}

void pratique::pas(int d){
    x+=d;
}
















