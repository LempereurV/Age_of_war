#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;

#include <iostream>
using namespace std;


#include <ctime>

#include"pratique.h"
#include"theorique.h"
#include"tourelle.h"
#include"Interface.h"
#include"theorique.h"
#include <ctime>

const int freqDisplay = 100;



float start = static_cast<float>(std::time(nullptr)); // constante globale de l'heure de début


int main(){
    vector<pratique> armee1;
    vector<pratique> armee2;
    int epoque=0;
    base base1;
    base base2;
    creer_bases(epoque, base1, base2);
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
            armee1[0].refresh(armee1,armee2,base1,base2);
            armee2[0].refresh(armee1,armee2,base1,base2);
            base1.maj();
            base2.maj();
            noRefreshEnd();
            milliSleep(50);
        }
    }
}
