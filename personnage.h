#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#endif // PERSONNAGE_H
#include<vector>
using namespace std ;

class pratique{
    int x;
    int vie;
    int camp;
public:
    void creer(int pos,int c,vector<pratique> armee1,vector<pratique> armee2);
    void avancer(vector<pratique> armee1,vector<pratique> armee2);
    void attaquer(pratique ennemi);
    void mourir();
};
