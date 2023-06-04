#include "pratique.h"
#include <iostream>
#include<vector>
#include <unistd.h>
using namespace std ;

/* ===================================================== ~~~ BASE ~~~ ========================================================================= */

base::base(){ // constructeur - initialise les valeurs (epoque, viemax, exp)
    epoque = 0;
    degats = 0;
    viemax = _vie_[0];
    exp = 0;
}

base::~base(){} // destructeur

void base::init(int _camp_){ // initialise les valeurs (x0, camp)
    camp = _camp_;
    x0 = 235 + 560 * _camp_;
    //x0 = 20 + 775 * _camp_;
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
    _soldat_.x = 200 + 600*(_camp_==1);                     // Position de départ
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
void pratique::update_vie(int _degats_) {vie-= _degats_;}     // actualise la vie

// FONCTIONS D'ACTION
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

int pas = 3;
void avance(vector<pratique>& armee, bool contact, double time) {
    for (int i=0; i<int(armee.size()); i++) {
        if (i!=0 or not(contact)){ // time >= armee[i].get_time_pop() and
            if (i==0 or (i!=0 and abs(armee[i].get_x() - armee[i-1].get_x()) > 20+10* (armee[i].get_largeur() + armee[i-1].get_largeur())) ){
                // On avance les soldats possibles jusqu'à ce qu'ils soient au moins un pas derrière le précédent
                // fonction linéaire f : f(camp=0)=+1 // f(camp=1)=-1 : f(camp) = 1-2camp
                int d = pas * (1 - 2 * armee.at(i).get_camp()); // distance à ajouter à la position x
                armee[i].update_x( armee.at(i).get_x()+d );
            }
        }
    }
}

void combat(vector<pratique>& armee1,vector<pratique>& armee2, base& base1) {
    // les deux têtes se frappent
    cout << "  --> e1 " << armee1[0].get_vie() << " ";
    armee1[0].update_vie(armee2[0].get_force());
    cout << armee1[0].get_vie() << endl;
    cout << "  --> e1 " << armee2[0].get_vie() << " ";
    armee2[0].update_vie(armee1[0].get_force());
    cout << armee2[0].get_vie() << endl;
    // Supperssion en cas de mort aka la vie est négative
    cout << "  --> e3" << endl;
    if (armee1[0].get_vie()<=0){armee1.erase(armee1.begin());}
    cout << "  --> e4" << endl;
    if (armee2[0].get_vie()<=0){base1.exp+=10*armee2[0].get_exp();armee2.erase(armee2.begin());}
}

void approach(vector<pratique> armee, base& base) {
    base.degats+=armee[0].get_force();
}

void moveSoldiers(vector<pratique>& armee1,vector<pratique>& armee2, base& base1, base& base2, double time) {
    if (armee1.size()>0 and armee2.size()>0 and armee1.at(0).distance(armee2.at(0)) < 15*(armee1[0].get_largeur()+armee2[0].get_largeur())) {
        // Les deux permiers membres sont l'un face à l'autre : il y a pas contact ⇒ contact = true
        cout << "  in_if" << endl;
        combat(armee1, armee2, base1);
        if (armee1.size()>0){
            cout << "  armee1" << endl;
            avance(armee1, true, time);
        }
        if (armee2.size()>0){
            cout << "  armee2" << endl;
            avance(armee2, true, time);
        }
    }
    else if (armee1.size()>0 and abs(armee1[0].get_x() -base2.x0) <35){
        approach(armee1, base2);
    }
    else if (armee2.size()>0 and abs(armee2[0].get_x() +100 -base1.x0) <35){
        approach(armee2, base1);
    }
    else {
        // Tout le monde avance : il n'y a pas contact ⇒ contact = false
        avance(armee1, false, time);
        avance(armee2, false, time);
    }

}

