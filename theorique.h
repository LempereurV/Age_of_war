#pragma once

struct theorique{
    int viemax;
    int force;
    int epoque;
    int portee;
    double frequence;
    int cout;
    int prime;
    double temps;
    int largeur;
    int exp;
};

static theorique global[16]={
    {40,7,0,1,1,15,20,1.5,2,10}, //clubman
    {24,7,0,15,1.3,25,33,1.5,2,15}, //lance-pierre
    {100,17,0,1,1,100,130,3,6,50}, //chevaucheur de dino
    {65,14,1,1,1,50,65,2.5,2,40}, //épée
    {80,14,1,20,1.3,75,98,2.5,2,60}, //arbalète
    {150,35,1,2,1,500,650,6,12,150}, //chevalier # temps = 3
    {100,30,2,1,1,200,260,3.5,2,120}, //duellier
    {120,44,2,20,1,400,520,3.5,2,150}, //mousquetaire
    {440,75,2,1,1,1000,1300,7,2,500}, //cannonier
    {550,120,3,3,1,1500,1950,3,2,450}, //couteau
    {700,200,3,15,1.5,2000,2600,3,2,600}, //fantassin
    {2000,500,3,3,1,7000,9100,9,16,2000}, //tank
    {1900,450,4,3,1,5000,6500,2.5,2,1500}, //super-épée
    {3000,500,4,15,1.3,6000,7200,2.5,2,2200}, //soldat du futur
    {8000,1000,4,3,0.7,20000,26000,9,12,7000}, //tank du futur
    {6000,4000,4,15,1.5,150000,19000,9,2,10000}, //soldat d'élite
 };
//{vie, degats, epoque, portee, frequence, cout, prime, temps de chargement, (largeur)

static int requis[4]={
    4000,12000,40000,120000
};
