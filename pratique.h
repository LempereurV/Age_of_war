#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "theorique.h"
#include "tourelle.h"
#endif // PERSONNAGE_H
#include<vector>
using namespace std ;


class pratique{
    int x;
    int vie;
    int camp;
    theorique proprietes;
public:
    void creer(int pos,int c,vector<pratique> armee1,vector<pratique> armee2);
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2,int argent[2]);
    void refresh(int degats, int camp, vector<pratique> armee1, vector<pratique> armee2,int argent[2]);
    bool reach(int xA,int portee);
    int distance(pratique ennemi);
    void pas(int p);
};

void avancer(vector<pratique> armee1,vector<pratique> armee2);

struct base{
    int x0;
    int camp;
    int epoque;
    int viemax;
    bool tour1;
    bool tour2;
    bool tour3;
    tourelle T1;
    tourelle T2;
    tourelle T3;
};


