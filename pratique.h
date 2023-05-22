#pragma once
#include "theorique.h"
#include<vector>
using namespace std ;

struct base{
    int x0;
    int camp;
    int epoque;
    int viemax;
    int vie;
    int exp;
    int argent;
    bool test_epoque();
    void maj();
};

class pratique{
    int x;
    int vie;
    int camp;
    theorique proprietes;
public:
    void creer(int pos,int c,vector<pratique> armee1,vector<pratique> armee2);
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2,base base1, base base2);
    void refresh(vector<pratique> armee1, vector<pratique> armee2, base base1, base base2);
    bool reach(int xA,int portee);
    int distance(pratique ennemi);
    void pas(int p);
};

void avancer(vector<pratique> armee1,vector<pratique> armee2);
void creer_bases(int epoque, base base1, base base2);
