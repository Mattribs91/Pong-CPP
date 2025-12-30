//
// Created by Matt on 29/12/2025.
//

#ifndef PONG_C_BALLE_H
#define PONG_C_BALLE_H
#include <SDL.h>

class Balle {
private:
    int _positionX;
    int _positionY;

public:
    Balle();
    Balle(int positionX, int positionY);
    void afficher(SDL_Renderer* lePinceau) const;
    void monter();
    void droite();
    bool toucheMur() const;
    void getY() const;
};


#endif //PONG_C_BALLE_H