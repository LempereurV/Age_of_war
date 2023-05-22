#include <string>
#include <iostream>
using namespace std;

void displayMenu(int epoque); // affiche la barre des choix
void getSize(const string& filePath, int& width, int& height);
void processClickAction(int x, int y, int epoque, int windowWidth, int windowHeight);
void getActionMenu(int x, int y, int epoque);

