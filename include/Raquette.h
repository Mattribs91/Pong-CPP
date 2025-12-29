//
// Created by Matt on 29/12/2025.
//

#ifndef PONG_C_RAQUETTE_H
#define PONG_C_RAQUETTE_H
#include "SDL.h"

class Raquette {
private:
    int _positionX;
    int _positionY;

public:
    Raquette();
    Raquette(int positionX, int positionY);
    void afficher(SDL_Renderer* lePinceau) const;
    bool toucheBalle() const;
    void getY() const;
};

#endif //PONG_C_RAQUETTE_H