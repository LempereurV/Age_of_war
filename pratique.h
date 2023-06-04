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
    double get_duree_formation() {return proprietes.temps;};
    int get_force() {return proprietes.force;};
    int get_vie() {return vie;};
    int get_exp() {return proprietes.exp;} // renvoie l'experience de la mort du perso
    int get_largeur() {return proprietes.largeur;}
    // fonction d'update
    void update_x(int _x_);
    void update_vie(int _degats_);
    // fonction d'action
    void attaquer(pratique ennemi);
    void mourir(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2);
    void refresh(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2);
    bool reach(int xA, int portee);
    int distance(pratique ennemi);
    void pas(int p);
};


const int _vie_[5] = {500, 1100, 2000, 3200, 4700}; // liste des vies maximales de la base par époque
const int _exp_[5] = {4000, 14000, 45000, 200000};  // liste des experiences nécessaires pour changer d'apoque


// Fonctions d'action sur la classe pratique
void avance(vector<pratique>& armee, bool contact, double time);
void moveSoldiers(vector<pratique>& armee1,vector<pratique>& armee2, base& base1, base& base2, double time);
