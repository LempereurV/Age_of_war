#include "pratique.h"
#include <iostream>
#include<vector>
#include <unistd.h>
using namespace std ;

/* ===================================================== ~~~ BASE ~~~ ========================================================================= */

int _vie_[5] = {500, 1100, 2000, 3200, 4700}; // liste des vies maximales de la base par époque
int _exp_[5] = {4000, 14000, 45000, 200000};  // liste des experiences nécessaires pour changer d'apoque

base::base(){ // constructeur - initialise les valeurs (epoque, viemax, exp)
    epoque = 0;
    viemax = _vie_[0];
    exp = 0;
}

base::~base(){} // destructeur

void base::init(int _camp_){ // initialise les valeurs (x0, camp)
    camp = _camp_;
    if (_camp_==0){
        x0 = 200;
    } else {
        x0 = 700;
    }
}

bool base::test_epoque(){
    return (exp > _exp_[epoque]);
}

/* =========================================================================================================================================== */

void pratique::creer(int index, int _camp_, vector<pratique> armee1, vector<pratique> armee2){
    int x0=0;
    if (_camp_==1)
        x0=100;
    pratique soldat;
    soldat.proprietes = global[index];
    soldat.x = x0;
    soldat.vie = soldat.proprietes.viemax;
    soldat.camp = _camp_;
    sleep(soldat.proprietes.temps);
    if(_camp_==0){
        armee1.push_back(soldat);
    }
    else
        armee2.push_back(soldat);
};

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
        argent[1]+=2*proprietes.prime;
        base2.exp+=proprietes.exp;
    }
    else{
        armee2.pop_back();
        argent[0]+=proprietes.prime;
        base1.exp+=proprietes.exp;
    }
}

void pratique::refresh(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2){
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


/* =========================================================================================================================================== */

// Fonction pour incrémenter les positions des deux armées
void avancer(vector<pratique> armee1, vector<pratique> armee2){
    if(armee1[0].distance(armee2[0])>1){
        for (auto it = armee1.begin(); it != armee1.end(); ++it) {
            (*it).pas(1); // les élements de l'armée 1 avancent selon +ex
        }
        for (auto it = armee2.begin(); it != armee2.end(); ++it){
            (*it).pas(-1); // les élements de l'armée 1 avancent selon -ex
        }
    }
}









