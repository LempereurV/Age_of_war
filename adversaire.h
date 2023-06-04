#pragma once

#include "pratique.h"

void entr();

void ageSteps(int steps[4]);
void ageChange(base base1, base& base2, int steps[4]);
int selec_i(base base1, int steps[4]);
void updateOppArmy(base base1, base& base2, vector<pratique>& armee2, int steps[4], int time);
void updateOppArmy(base& base2, vector<pratique>& armee2, int time);
double lognormalDistribution();

bool victoire(base base1, base base2);
bool WhoWins(base base1, base base2);
