#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#endif // PERSONNAGE_H


class pratique{
    int x;
    int pos;
    int vie;
    int camp;
public:
    pratique creer(int pos,int camp);
    void attaquer(pratique ennemi);
    void mourir();
};
