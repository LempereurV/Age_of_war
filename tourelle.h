#ifndef TOURELLE_H
#define TOURELLE_H

#include "pratique.h"

struct data_tourelle{
    int portee;
    double periode;
    int degats;
    int prix;
    // int remboursement; : since the reinbursing is always at the half of the cost
    // visuels plus tard
    };

struct tourelle{
    int camp;
    data_tourelle data;
public:
    tourelle(int call_camp, int id);
    void tir_tourelle(vector<pratique> armee1, vector<pratique> armee2);
};

int largeur = 100; // largeur en pixel de la scène

data_tourelle global_t[16] = {
    {0, 1, 0, 0}, // Null /// PENSER A SES VISUELS NULS
    {largeur, 3, 3, 100}, // Rock slingshot
    {largeur, 3, 3, 200}, // Egg automatic
    {largeur, 2, 8, 500}, // Primitive catapult
    {largeur, 2, 7, 500}, // Catapult
    {largeur, 2, 7, 750}, // Fire turrets
    {largeur, 2, 17, 1000}, // Oil
    {largeur, 1.5, 15, 1500}, // Small Canon
    {largeur, 1.4, 22, 3000}, // Large Canon
    {largeur, 1.2, 37, 6000}, // Expensive canon
    {largeur, 1, 60, 7000}, // Single turret
    {largeur, 1, 100, 9000}, // Rocket turret
    {largeur, 1, 250, 14000}, // Double turret
    {largeur, 0.9, 300, 24000}, // Titanium shooter
    {largeur, 0.75, 700, 40000}, // Lazer Canon
    {largeur, 0.5, 1250, 100000} // Ion Ray
};


#endif // TOURELLE_H
