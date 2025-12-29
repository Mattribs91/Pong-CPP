//
// Created by Matt on 29/12/2025.
//

#include "Raquette.h"
#include <iostream>
#include "Moteur.h"

using namespace std;

Raquette::Raquette() {
    _positionX = 0;
    _positionY = 0;
}

Raquette::Raquette(int positionX, int positionY) {
    _positionX = positionX;
    _positionY = positionY;
}

void Raquette::afficher(SDL_Renderer* lePinceau) const {
    SDL_SetRenderDrawColor(lePinceau, 255, 255, 255, 255);
    SDL_Rect rect;

    rect.x = _positionX;
    rect.y = _positionY;
    rect.w = 20;
    rect.h = 50;

    SDL_RenderFillRect(lePinceau, &rect);
}
