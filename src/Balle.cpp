//
// Created by Matt on 29/12/2025.
//

#include "Balle.h"
#include <iostream>
#include "Moteur.h"

using namespace std;

Balle::Balle() {
    _positionX = 0;
    _positionY = 0;
}

Balle::Balle(int positionX, int positionY) {
    _positionX = positionX;
    _positionY = positionY;
}

void Balle::afficher(SDL_Renderer* lePinceau) const {
    SDL_SetRenderDrawColor(lePinceau, 255, 255, 255, 255);
    SDL_Rect rect;

    rect.x = _positionX;
    rect.y = _positionY;
    rect.w = 20;
    rect.h = 20;

    SDL_RenderFillRect(lePinceau, &rect);
}

void Balle::monter() {
    _positionY += 1;
}

void Balle::droite() {
    _positionX += 1;
}

bool Balle::toucheMur() const {
    if (_positionY < 0) {
        return true;
    }

    if (_positionY >= HAUTEUR_FENETRE * 5) {
        return true;
    }

    return false;
}

void Balle::getY() const {
    cout << _positionY << endl;
}
