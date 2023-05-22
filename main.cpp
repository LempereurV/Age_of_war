#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
using namespace std;

#include <ctime>

#include"pratique.h"
#include"theorique.h"
#include"tourelle.h"

const int freqDisplay = 100;

int main(){
    int W = 500, H = 500;
    openWindow(W,H);

}

float start = static_cast<float>(std::time(nullptr)); // constante globale de l'heure de début

/*
int main(){
    vector<pratique> armee1;
    vector<pratique> armee2;
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            avancer(armee1,armee2);
            noRefreshEnd();
            milliSleep(50);
        }
    }}
*/
