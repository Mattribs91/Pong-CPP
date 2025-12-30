//
// Created by Matt on 29/12/2025.
//

#include "Raquette.h"
#include "Moteur.h"
#include <iostream>


using namespace std;

Raquette::Raquette() {
  _positionX = 0;
  _positionY = 0;
}

Raquette::Raquette(float positionX, float positionY) {
  _positionX = positionX;
  _positionY = positionY;
}

void Raquette::afficher(SDL_Renderer *lePinceau) const {
  SDL_SetRenderDrawColor(lePinceau, 255, 255, 255, 255);
  SDL_Rect rect;

  rect.x = (int)_positionX;
  rect.y = (int)_positionY;
  rect.w = 20;
  rect.h = 120;

  SDL_RenderFillRect(lePinceau, &rect);
}

void Raquette::descendre(double dt) {
  float vitesse = 600.0f; // Pixels par seconde
  _positionY += vitesse * dt;
}

void Raquette::monter(double dt) {
  float vitesse = 600.0f; // Pixels par seconde
  _positionY -= vitesse * dt;
}

bool Raquette::peutMonter() const {
  if (_positionY < 10) {
    return false;
  }

  return true;
}

bool Raquette::peutDescendre() const {
  if (_positionY > HAUTEUR_FENETRE * 5 - 130) {
    return false;
  }

  return true;
}

float Raquette::getY() const {
  return _positionY;
}

float Raquette::getX() const {
    return _positionX;
}
