//
// Created by Matt on 29/12/2025.
//

#ifndef PONG_C_RAQUETTE_H
#define PONG_C_RAQUETTE_H
#include "SDL.h"

class Raquette {
private:
  float _positionX;
  float _positionY;

public:
  Raquette();
  Raquette(float positionX, float positionY);
  void afficher(SDL_Renderer *lePinceau) const;

  bool toucheBalle() const;

  float getY() const;
  float getX() const;

  void monter(double dt);
  void descendre(double dt);

  bool peutMonter() const;
  bool peutDescendre() const;
};

#endif // PONG_C_RAQUETTE_H