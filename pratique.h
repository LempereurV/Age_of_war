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
    int degats; // variable de dégâts subis
    int viemax; // vie maximale de la base en fonction de l'époque
    int exp;    // variable d'experience
// Fonctions
    base();
    ~base();
    void init(int camp);
    bool test_epoque();
    void update_viemax(int epoque);
};

// Structure pour les personnages en pratique
class pratique{
    int x;      // position actuelle sur le champ de bataille si affiché
    int vie;    // vie actuelle non consultable en jeu
    int camp;   // numéro du camp ∈{0,1}
    int index;  // type de soldat
    theorique proprietes;
    double time_pop;
public:
    // initialisations
    pratique();
    ~pratique();
    void initialize(int index, int _camp_, vector<pratique> &armee, double time);
    // fonction de lecture
    int get_x();
    int get_camp();
    int get_index();
    double get_time_pop();
    // fonction d'update
    void update_x(int _x_);
    // fonction d'action
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2);
    void refresh(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2);
    bool reach(int xA, int portee);
    int distance(pratique ennemi);
    void pas(int p);
};

// Fonctions d'action sur la classe
void avancer(vector<pratique> armee1,vector<pratique> armee2);
void avance(vector<pratique>& armee, bool contact);
void moveSoldiers(vector<pratique>& armee1,vector<pratique>& armee2);
void test_x(vector<pratique> armee);
