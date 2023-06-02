#include "pratique.h"
#include <iostream>
#include<vector>
#include <unistd.h>
#include "Interface.h"
using namespace std ;
#include <string>
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
using namespace Imagine;

bool base::test_epoque(){
    return (exp>requis[epoque]);
}

void pratique::creer_soldat(int pos, int c){
    int x0=0;
    if (c==1)
        x0=100;
    poste=pos;
    proprietes=global[pos];
    x=x0;
    vie= proprietes.viemax;
    camp=c;
    sleep( proprietes.temps);
};

void integ(int camp,vector<pratique> armee1,vector<pratique> armee2,pratique soldat){
    if(camp==0){
        armee1.push_back(soldat);
    }
    else
        armee2.push_back(soldat);
}

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

void pratique::attaquer(pratique ennemi,vector<pratique> armee1, vector<pratique> armee2,base base1, base base2){
    if(reach(ennemi.x,proprietes.portee)){
        while(vie>0){
            ennemi.vie-=proprietes.force;
            sleep(proprietes.frequence/2);
        }
        mourir(armee1,armee2,base1,base2);
    }
}

void pratique::mourir(vector<pratique> armee1, vector<pratique> armee2,base base1, base base2){
    if(camp==0){
        armee1.pop_back();
        base2.argent+=2*proprietes.prime;
        base2.exp+=proprietes.exp;
    }
    else{
        armee2.pop_back();
        base2.argent+=proprietes.prime;
        base1.exp+=proprietes.exp;
    }
}

void pratique::refresh(vector<pratique> armee1, vector<pratique> armee2, base base1, base base2){
    if (vie<0){
        mourir(armee1, armee2, base1, base2);
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

void creer_bases(int epoque, base base1, base base2){
    base1.exp=0;
    base2.exp=0;
    base1.argent=175;
    base2.argent=175;
    base1.epoque=epoque;
    base2.epoque=epoque;
    base1.x0=0;
    base2.x0=100;
    base1.viemax=viecamp[epoque];
    base2.viemax=viecamp[epoque];
}

void base::maj(int windowWidth, int windowHeight){
    if (test_epoque()){
        epoque+=1;
        viemax=viecamp[epoque];
        vie=viemax-vie;}
    affichage_base(epoque,camp,windowWidth,windowHeight);
}

void pratique::afficher_soldat(){
    int W, H;
    byte *r,*g,*b;
    if (poste==0)
        loadColorImage(srcPath("Prehistoire_cac.png"), r, g, b, W, H);
    if (poste==1)
        loadColorImage(srcPath("Prehistoire_tir.png"), r, g, b, W, H);
    if (poste==2)
        loadColorImage(srcPath("Prehistoire_mon.png"), r, g, b, W, H);
    if (poste==3)
        loadColorImage(srcPath("M-A_cac.png"), r, g, b, W, H);
    if (poste==4)
        loadColorImage(srcPath("M-A_tir.png"), r, g, b, W, H);
    if (poste==5)
        loadColorImage(srcPath("M-A_mon.png"), r, g, b, W, H);
    if (poste==6)
        loadColorImage(srcPath("Renaissance_cac.png"), r, g, b, W, H);
    if (poste==7)
        loadColorImage(srcPath("Renaissance_tir.png"), r, g, b, W, H);
    if (poste==8)
        loadColorImage(srcPath("Renaissance_mon.png"), r, g, b, W, H);
    if (poste==9)
        loadColorImage(srcPath("Contemporain_cac.png"), r, g, b, W, H);
    if (poste==10)
        loadColorImage(srcPath("Contemporain_tir.png"), r, g, b, W, H);
    if (poste==11)
        loadColorImage(srcPath("Contempoarin_mon.png"), r, g, b, W, H);
    if (poste==12)
        loadColorImage(srcPath("Futur_cac.png"), r, g, b, W, H);
    if (poste==13)
        loadColorImage(srcPath("Futur_tir.png"), r, g, b, W, H);
    if (poste==14)
        loadColorImage(srcPath("Futur_mon.png"), r, g, b, W, H);
    putColorImage(x, 0, r, g, b, W, H);
}
