//
// Created by julie on 13/05/2025.
//

#include "Compteur.h"


Compteur* Compteur::instance = nullptr;

Compteur::Compteur() : points(0) {
}


Compteur& Compteur::getInstance() {
    if (!instance) {
        instance = new Compteur();
    }

    return *instance;
}

void Compteur::addPoints() {
    points++;
    if (points > 99) {
        points = 99;
    }
}

unsigned char* Compteur::getSpriteDizaine(){
    int dizaine = points / 10;
    unsigned char* sprite; 
    if (dizaine == 0) 
        sprite = ZERO;
    else if (dizaine == 1) 
        sprite = ONE;
    else if (dizaine == 2)
        sprite = TWO;
    else if (dizaine == 3)
        sprite = THREE;
    else if (dizaine == 4)
        sprite = FOUR;
    else if (dizaine == 5)
        sprite = FIVE;
    else if (dizaine == 6)
        sprite = SIX;
    else if (dizaine == 7)
        sprite = SEVEN;
    else if (dizaine == 8)
        sprite = EIGHT;
    else if (dizaine == 9)
        sprite = NINE;
    return sprite;
}
unsigned char* Compteur::getSpriteUnite(){
    int dizaine = points % 10;
    unsigned char* sprite; 
    if (dizaine == 0) 
        sprite = ZERO;
    else if (dizaine == 1) 
        sprite = ONE;
    else if (dizaine == 2)
        sprite = TWO;
    else if (dizaine == 3)
        sprite = THREE;
    else if (dizaine == 4)
        sprite = FOUR;
    else if (dizaine == 5)
        sprite = FIVE;
    else if (dizaine == 6)
        sprite = SIX;
    else if (dizaine == 7)
        sprite = SEVEN;
    else if (dizaine == 8)
        sprite = EIGHT;
    else if (dizaine == 9)
        sprite = NINE;
    return sprite;
}

