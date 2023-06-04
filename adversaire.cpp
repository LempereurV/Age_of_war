#include <ctime>
#include <random>
#include <chrono>
#include "pratique.h"
#include "theorique.h"

#include <random>
#include <cmath>

#include <iostream>
using namespace std;


/* =================================== ~~~~~~ OBSOLETE GESTION DU TEMPS ~~~~~~ =================================================*/

void timeNextPlay(float &next_play, float max){
    // Générer un nombre flottant aléatoire entre 0.0 et max (secondes)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, max);
    float random_seconds = distribution(gen);

    // Ajouter la durée aleatoire au temps next_play
    next_play += random_seconds;
}

void playAdversaire(int epoque,vector<pratique> armee1,vector<pratique> armee2){
    pratique soldat;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(3*epoque, 3*epoque+3);
    int pos = distribution(gen);
    //soldat.creer_soldat(pos,1);
    //integ(1,armee1,armee2,soldat);
}

void decisionAdversaire(float next_play, int epoque,vector<pratique> armee1,vector<pratique> armee2){
    float current = static_cast<float>(std::time(nullptr)); // temps courant
    if (next_play > current){ // c'est que c'est à nous de jouer !!!
        playAdversaire(epoque,armee1,armee2);
        timeNextPlay(next_play, 30.0);
    }
}

/* =========================================== ~~~~~~ JEU ADVERDSAIRE ~~~~~~ =================================================== */
/*  Stratégie :
    - On veut que l'adversaire définisse une liste des 4 temps où il changera de niveau : fonction de notre propre avancée à valeur±10%
    - A chaque tiers, l'adversaire débloque un nouveau joueur :
        à un instant dans le tiers i (par exemple le tiers 4 est le 5ème tiers soit le 2ème de l'époque n°2)
        on possède les i/3+1 (ici 4/3+1=2) premiers soldats de l'époque
    - Enfin on joue au hasard : on ajoute un soldat avec un timepop random
*/

// Liste des 4 changements d'époques
void ageSteps(int steps[4]) {
    for (int i=0; i<4; i++){
        steps[i] = int(_exp_[i]*(0.9+2*(rand()/327670.)));
    }
}

void ageChange(base base1, base& base2, int steps[4]) {
    if (base1.exp > steps[base2.epoque]){
        // On a une experience supérieure à celle
        // nécessaire de passage de l'époque adversaire
        base2.viemax= _vie_[base2.epoque++];
    }
}

/* Jeu de l'adversaire
    • initialisation : on ajoute un soldat en cohérence avec ceux possibles (donc juste le n°0)
    • hérédité : losque le soldat est poppable, on le pop et on ajoute un soldat en cohérence avec ceux possibles
*/

double lognormalDistribution() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::lognormal_distribution<double> distribution(0.0, 3.0);
    return 3*distribution(gen);
}

// Selection de l'indice des soldats possibles
int selec_i(base base1, int steps[4]) {
    int exp[15];
    exp[0] = 0; exp[1] = steps[0]/3; exp[2] = 2*steps[0]/3;
    for (int i=1; i<4; i++){
        exp[3*i] = steps[i-1];
        exp[3*i+1] = (2*(i>0)*steps[i-1] + steps[i])/3;
        exp[3*i+2] = ((i>0)*steps[i-1] + 2*steps[i])/3;
    }
    for (int i=1; i<12; i++){
        if (base1.exp < exp[i]){
            return i-1;
        }
    }
    return 14;
}

/*
void updateOppArmy(base base1, base& base2, vector<pratique>& armee2, int steps[4], int time) {
    int i = selec_i(base1, steps);
    int index;
    if (i!=0){
        index = rand() % i; // on selectionne un type de soldat possible
    } else {
        index = 0;
    }
    pratique _soldat_;
    if (time > armee2.back().get_time_pop()){
        double delta = lognormalDistribution();
        while (delta<1.5){
            delta = lognormalDistribution();
        }
        cout << "next_time = " << delta << endl;
        _soldat_.initialize(index, 1, armee2, time + delta);
    }
}
*/

void updateOppArmy(base& base2, vector<pratique>& armee2, int time) {
    cout << "updateOppArmy - time = " << time << endl;
    for (int i=0; i<int(armee2.size()); i++){
        cout << "  " << i << " " << armee2[i].get_time_pop() << endl;
    }
    cout << "  back " << armee2.back().get_time_pop() << endl;
    if (time > armee2.back().get_time_pop()){
        cout << "  in_if" << endl;
        pratique _soldat_;
        _soldat_.initialize(3 * base2.epoque + rand()%3, 1, armee2, time+lognormalDistribution()); // rand()%10
    }
}


/* ================================================ ~~~~~ VICTOIRES ~~~~~ =======================================================*/

bool victoire(base base1, base base2) {
    // Quelqu'un a gagné
    return (base1.degats > base1.viemax || base2.degats > base2.viemax);
}

bool WhoWins(base base1, base base2) {
    // Test victoire de l'ennemi
    return (base1.degats > base1.viemax);
}
