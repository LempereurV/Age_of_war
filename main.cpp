#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>

using namespace std;
#include"pratique.h"
#include"theorique.h"
#include"tourelle.h"
#include"Interface.h"
#include <ctime>

const int freqDisplay = 100;


int main(){
    vector<pratique> armee1;
    vector<pratique> armee2;
    int epoque=0;
    int argent[2]={175,175};
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            affichage(epoque);
            avancer(armee1,armee2);
            noRefreshEnd();
            milliSleep(50);
        }
    }}
