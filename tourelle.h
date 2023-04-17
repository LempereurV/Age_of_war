#ifndef TOURELLE_H
#define TOURELLE_H

struct tourelle{
    int portee;
    double periode;
    int degats;
    int prix;
    int remboursement;
    // visuels plus tard
    };

int largeur = ?; // laurgeur en pixel

tourelles global_t[n] = {
    {largeur, 3, ___, 100, /2}; // Rock slingshot
    {largeur, 3, ___, 200, }; // Egg automatic
    {largeur, 2, ___, 500, }; // Primitive catapult
    {largeur, 2, ___, 500, }; // Catapult
    {largeur, 2, ___, 750, }; // Fire turrets
    {largeur, 2, ___, 1000, }; // Oil
    {largeur, 1.5, ___, 1500, }; // Small Canon
    {largeur, 1.4, ___, 3000, }; // Large Canon
    {largeur, 1.2, ___, 6000, }; // Expensive canon
    {largeur, 1, ___, 7000, }; // Single turret
    {largeur, 1, ___, 9000, }; // Rocket turret
    {largeur, 1, ___, 14000, }; // Double turret
    {largeur, 0.9, ___, 24000, }; // Titanium shooter
    {largeur, 0.75, ___, 40000, }; // Lazer Canon
    {largeur, 0.5, ___, 100000, }; // Ion Ray
    };


#endif // TOURELLE_H
