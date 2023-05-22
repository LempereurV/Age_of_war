#include <ctime>
#include <random>
#include <chrono>

void timeNextPlay(float &next_play, float max) {
    // Générer un nombre flottant aléatoire entre 0.0 et max (secondes)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, max);
    float random_seconds = distribution(gen);

    // Ajouter la durée aleatoire au temps next_play
    next_play += random_seconds;
}

void playAdversaire(){

}

void decisionAdversaire(float next_play){
    float current = static_cast<float>(std::time(nullptr)); // temps courant
    if (next_play > current){ // c'est que c'est à nous de jouer !!!
        playAdversaire();
        timeNextPlay(next_play, 30.0);
    }
}
