//
// Created by Matt on 29/12/2025.
//

#ifndef PONG_C_BALLE_H
#define PONG_C_BALLE_H
#include <SDL.h>
#include "Raquette.h"

class Balle {
private:
  float _positionX;
  float _positionY;
  float _vitesseX;
  float _vitesseY;

public:
  Balle();
  Balle(float positionX, float positionY, float vitesseX, float vitesseY);
  void afficher(SDL_Renderer *lePinceau) const;
  void monter();
  void avancer(double dt);

  bool sortGauche() const;
  bool sortDroite() const;
  void getY() const;

  bool toucheRaquette(const Raquette &raquette) const;
  void rebondir(const Raquette &raquette);

  void rebondMurs();

  void reinitialiser();
};

#endif // PONG_C_BALLE_H