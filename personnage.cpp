#include "pratique.h"
#include <iostream>
#include<vector>
#include <unistd.h>
using namespace std ;

/* ===================================================== ~~~ BASE ~~~ ========================================================================= */

int _vie_[5] = {500, 1100, 2000, 3200, 4700}; // liste des vies maximales de la base par époque
int _exp_[5] = {4000, 14000, 45000, 200000};  // liste des experiences nécessaires pour changer d'apoque

base::base(){ // constructeur - initialise les valeurs (epoque, viemax, exp)
    epoque = 0;
    degats = 0;
    viemax = _vie_[0];
    exp = 0;
}

base::~base(){} // destructeur

void base::init(int _camp_){ // initialise les valeurs (x0, camp)
    camp = _camp_;
    if (_camp_==0){
        x0 = 200;
    } else {
        x0 = 700;
    }
}

bool base::test_epoque(){
    return (exp > _exp_[epoque]);
}

void base::update_viemax(int epoque) {
    viemax = _vie_[epoque];
}

/* =========================================================================================================================================== */

pratique::pratique(){}
pratique::~pratique(){}

/* ~~~~ UNE SOLUTION ALTERNATIVE EST DE METTRE UNE POSITION DÉPENDANTE DU TEMPS : LE PERSO A UNE POSITION FONCTION DU TEMPS ~~~~ */
/*void pratique::créer(int index, int _camp_, vector<pratique> armee1, vector<pratique> armee2){
    pratique soldat;
    soldat.proprietes = global[index];      // Selection du type de soldat
    soldat.x = 200 + 500*(_camp_==1);       // Position de départ
    soldat.vie = soldat.proprietes.viemax;  // Vie du soldat
    soldat.camp = _camp_;                   // Camp du soldat
    // Durée de formation du soldat : ~~~~~ MAUVAISE IDEE CAR BLOQUE TOUT LE RESTE DU JEU ~~~~~
    sleep(soldat.proprietes.temps);
    // AJOUT A UN CAMP
    if(_camp_==0){
        armee1.push_back(soldat);
    }
    else
        armee2.push_back(soldat);
};*/

void pratique::initialize(int index, int _camp_, vector<pratique> &armee, double time) { // Initialisation d'un soldat
    pratique _soldat_;
    _soldat_.proprietes = global[index];                    // Selection du type de soldat
    _soldat_.x = 200 + 500*(_camp_==1);                     // Position de départ
    _soldat_.vie = _soldat_.proprietes.viemax;              // Vie du soldat
    _soldat_.camp = _camp_;                                 // Camp du soldat
    _soldat_.index = index;                                 // Type de soldat
    _soldat_.time_pop = time + _soldat_.proprietes.temps;   // Instant d'apparition du soldat
    armee.push_back(_soldat_);                              // Ajout au camp
};

// FONCTIONS DE LECTURE
int pratique::get_x() {return x;}                   // return the position x which is private !
int pratique::get_camp() {return camp;}             // return the camp
int pratique::get_index() {return index;}           // return the index type of the soldier
double pratique::get_time_pop() {return time_pop;}  // return the time from which to display the soldier

// FONCTIONS D'ACTUALISATION
void pratique::update_x(int _x_) {x = _x_;}         // actualize the position

void pratique::attaquer(pratique ennemi){
    if(abs(x-ennemi.x)<proprietes.portee){
        while(vie>0){
            ennemi.vie-=proprietes.force;
            sleep(proprietes.frequence/2);
        }
    }
}

void pratique::mourir(vector<pratique> armee1, vector<pratique> armee2,int argent[2],base base1, base base2){
    if(camp==0){
        armee1.pop_back();
        argent[1]+=2*proprietes.prime;
        base2.exp+=proprietes.exp;
    }
    else{
        armee2.pop_back();
        argent[0]+=proprietes.prime;
        base1.exp+=proprietes.exp;
    }
}

void pratique::refresh(vector<pratique> armee1, vector<pratique> armee2, int argent[2], base base1, base base2){
    if (vie<0){
        mourir(armee1, armee2, argent, base1, base2);
    }
}

bool pratique::reach(int xA,int p){
    //xA: abscisse de celui qu'on considère et p sa portée
    return(abs(x-xA)<p);
}

int pratique::distance(pratique ennemi){
    return abs(x-ennemi.x);
}

void pratique::pas(int d){
    x+=d;
}


/* =========================================================================================================================================== */

// Fonction pour incrémenter les positions des deux armées
void avancer(vector<pratique> armee1, vector<pratique> armee2){
    if(armee1[0].distance(armee2[0])>1){
        for (auto it = armee1.begin(); it != armee1.end(); ++it) {
            (*it).pas(1); // les élements de l'armée 1 avancent selon +ex
        }
        for (auto it = armee2.begin(); it != armee2.end(); ++it){
            (*it).pas(-1); // les élements de l'armée 1 avancent selon -ex
        }
    }
}

/* =========================================================================================================================================== */

int pas = 5;

void avance(vector<pratique>& armee, bool contact) {
    //cout << "in_avance" << endl;
    for (int i=0; i<int(armee.size()); i++) {
        //cout << "  etape1 : i=" << i << endl;
        if (i!=0 or not(contact)){
            // On avance les soldats possibles jusqu'à ce qu'ils soient au moins un pas derrière le précédent

            // fonction linéaire f : f(camp=0)=+1 // f(camp=1)=-1 : f(camp) = 1-2camp
            int d = pas * (1 - 2 * armee.at(i).get_camp()); // distance à ajouter à la position x
            //cout << "  d = " << d << endl;
            //cout << "  before : x = " << armee.at(i).get_x() << endl;
            //cout << "  voulu  : x = " << 213 << endl; //armee.at(i).get_x()+d
            armee[i].update_x( armee.at(i).get_x()+d );
            //cout << "  after :  x = " << armee.at(i).get_x() << endl;
        }
    }
    test_x(armee);
    //cout << "out_avance" << endl;
}

void test_x(vector<pratique> armee) {
    for (int i=0; i<int(armee.size()); i++) {
        cout << "   - test_x = " << armee.at(i).get_x() << endl;
    }
}

void moveSoldiers(vector<pratique>& armee1,vector<pratique>& armee2) {
    if (armee1.size()>0 and armee2.size()>0 and armee1.at(0).distance(armee2.at(0)) > pas) {
        // Les deux permiers membres sont l'un face à l'autre : il y a pas contact ⇒ contact = true
        //combat(armee1, armee2);
        //avance(armee1, true);
        //avance(armee2, true);
    } else {
        cout << "etape1" << endl;
        // Tout le monde avance : il n'y a pas contact ⇒ contact = false
        avance(armee1, false);
        //test_x(armee1);
        avance(armee2, false);
    }

}

