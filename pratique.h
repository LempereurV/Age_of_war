#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "theorique.h"
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
    void avancer(vector<pratique> armee1,vector<pratique> armee2);
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2);
};

struct base{
    int epoque;
    int viemax;
    bool tour1;
    bool tour2;
    bool tour3;

};

