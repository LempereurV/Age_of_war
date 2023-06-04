#include <string>
#include <iostream>
using namespace std;

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "pratique.h"

// fonctions d'affichages génériques
void displayPicture(const std::string & file, bool debut, int windowWidth, int windowHeight, int positionX, int positionY); // ne fonctionne pas bien
void getSize(const string& filePath, int& width, int& height);

// fonctions d'affichages spécifiques
void displayMenu(int windowWidth); // affiche la barre des choix
void displayMenuCharac(int epoque, int windowWidth, int windowHeight); // affiche la barre des choix des personnages
void displayBase(int epoque1, int epoque2); // affiche les deux bases
void displayPers(int index); // affiche le personnage d'indice index (pers_index)
void afficherBackground(Window& window, int& width, int& height, int index, bool affiche); // affiche le background des Ponts
void displaySoldiers(vector<pratique> armee, int time);
void displayBaseHealth(base base1, base base2);
void displayEmptyBarre();

// Initializer
void initializeVisuals(int W, int epoque1, int epoque2, base base1, base base2, int& initialize, bool& test_initialize);

// fonctions d'actions d'affichages
void getActionMenu(int& x, int& y, int& epoque, int& etat, int time, vector<pratique>& armee1, base& base1, int& nbSpecial, int& initialize, bool& test_initialize, int windowWidth, int windowHeight, Window& window);


