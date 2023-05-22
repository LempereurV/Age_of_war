#pragma once
#include "theorique.h"
#include<vector>
using namespace std ;

struct base{
    int x0;
    int camp;
    int epoque;
    int viemax;
    int exp;
    bool test_epoque();
};

class pratique{
    int x;
    int vie;
    int camp;
    theorique proprietes;
public:
    void creer(int pos,int c,vector<pratique> armee1,vector<pratique> armee2);
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2,int argent[2],base base1, base base2);
    void refresh(vector<pratique> armee1, vector<pratique> armee2,int argent[2], base base1, base base2);
    bool reach(int xA,int portee);
    int distance(pratique ennemi);
    void pas(int p);
};

void avancer(vector<pratique> armee1,vector<pratique> armee2);
