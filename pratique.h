#pragma once
#include "theorique.h"
#include<vector>
using namespace std ;

// Structure pour les informations de la base
struct base{
// caracteristiques
    int x0;     // position initiale des attaquants
    int camp;   // numéro du camp ∈{0,1}
    int epoque; // numéro de l'époque ∈[0,5[
    int viemax; // vie maximale de la base en fonction de l'époque
    int exp;    // variable d'experience
// Fonctions
    base();
    ~base();
    void init(int camp);
    bool test_epoque();
};

// Structure pour les personnages en pratique
class pratique{
    int x;
    int vie;
    int camp;
    theorique proprietes;
public:
    void creer(int pos, int c, vector<pratique> armee1, vector<pratique> armee2);
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2);
    void refresh(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2);
    bool reach(int xA, int portee);
    int distance(pratique ennemi);
    void pas(int p);
};

// Fonctions d'action sur la classe
void avancer(vector<pratique> armee1,vector<pratique> armee2);
