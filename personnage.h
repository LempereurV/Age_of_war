#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#endif // PERSONNAGE_H


class pratique{
    int x;
    int pos;
    int vie;
    int posfile;
    int camp;
public:
    pratique creer(int pos);
    void attaquer(pratique ennemi);
    void mourir();
};
