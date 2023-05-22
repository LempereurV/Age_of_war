#include <ctime>
#include <random>
#include <chrono>
#include "pratique.h"
#include "theorique.h"

void timeNextPlay(float &next_play, float max) {
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
    soldat.creer_soldat(pos,1);
    integ(1,armee1,armee2,soldat);
}

void decisionAdversaire(float next_play, int epoque,vector<pratique> armee1,vector<pratique> armee2){
    float current = static_cast<float>(std::time(nullptr)); // temps courant
    if (next_play > current){ // c'est que c'est à nous de jouer !!!
        playAdversaire(epoque,armee1,armee2);
        timeNextPlay(next_play, 30.0);
    }
}
