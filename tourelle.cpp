#include <assert.h>
#include "tourelle.h"
#include "pratique.h"


tourelle::tourelle(int call_camp, int id){ // la clé id est le numero de la tourelle dans les données de global_t
    assert( (call_camp == 0 || call_camp ==  1) && id < 16 );
    data = global_t[id];
    camp = call_camp;
}

void tourelle::tir_tourelle(vector<pratique> armee1, vector<pratique> armee2){
    if (camp==0){
        if (armee2[0].reach(0, data.portee)){return;}
        armee2[0].refresh(data.degats, camp, armee1, armee2);
    }
    else{
        if (armee1[0].reach(largeur, data.portee)){return;}
        armee1[0].refresh(data.degats, camp, armee1, armee2);
    }
}
