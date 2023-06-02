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
    void maj(int windowWidth, int windowHeight);
};

class pratique{
    int x;
    int vie;
    int camp;
    int poste;
    theorique proprietes;
public:
    void creer_soldat(int pos,int c);
    void attaquer(pratique ennemi,vector<pratique> armee1, vector<pratique> armee2,base base1, base base2);
    void mourir(vector<pratique> armee1, vector<pratique> armee2,base base1, base base2);
    void refresh(vector<pratique> armee1, vector<pratique> armee2, base base1, base base2);
    bool reach(int xA,int portee);
    int distance(pratique ennemi);
    void pas(int p);
    void afficher_soldat();
};

void avancer(vector<pratique> armee1,vector<pratique> armee2);
void creer_bases(int epoque, base base1, base base2);
void integ(int camp,vector<pratique> armee1,vector<pratique> armee2,pratique soldat);
