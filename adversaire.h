#pragma once

#include "pratique.h"

// entr
void entr();

// obsolète : gestion du temps
void timeNextPlay(float &next_play, float max);
void playAdversaire(int epoque,vector<pratique> armee1,vector<pratique> armee2);
void decisionAdversaire(float next_play, int epoque,vector<pratique> armee1,vector<pratique> armee2);

// Gestion : Jeu Adversaire
void ageSteps(int steps[4]);                                           // obsolète
void ageChange(base base1, base& base2, int steps[4]);                 // obsolète
double lognormalDistribution();
int selec_i(base base1, int steps[4]);                                 // obsolète
void updateOppArmy(base& base2, vector<pratique>& armee2, int time);

// Gestion de la fin du jeu
bool victoire(base base1, base base2);
bool WhoWins(base base1, base base2);
