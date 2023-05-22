#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
using namespace std;

#include <ctime>

#include"pratique.h"
#include"theorique.h"
#include"tourelle.h"
#include"Interface.h"
#include <ctime>

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
    int epoque=0;
    int argent[2]={175,175};
    base base1;
    base base2;
    base1.exp=0;
    base2.exp=0;
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            affichage(epoque);
            avancer(armee1,armee2);
            for (auto it = armee1.begin(); it != armee1.end(); ++it) {
                (*it).attaquer(armee2[0]);
            }
            for (auto it = armee2.begin(); it != armee2.end(); ++it){
                (*it).attaquer(armee1[0]);
            }
            armee1[0].refresh(armee1,armee2,argent,base1,base2);
            armee2[0].refresh(armee1,armee2,argent,base1,base2);
            noRefreshEnd();
            milliSleep(50);
        }
    }}
*/
