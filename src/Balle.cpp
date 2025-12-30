//
// Created by Matt on 29/12/2025.
//

#include "Balle.h"
#include "Moteur.h"
#include <iostream>
#include "Raquette.h"


using namespace std;

Balle::Balle() {
  _positionX = 0;
  _positionY = 0;
}

Balle::Balle(float positionX, float positionY, float vitesseX, float vitesseY) {
  _positionX = positionX;
  _positionY = positionY;
  _vitesseX = vitesseX;
  _vitesseY = vitesseY;
}

void Balle::afficher(SDL_Renderer *lePinceau) const {
  SDL_SetRenderDrawColor(lePinceau, 255, 255, 255, 255);
  SDL_Rect rect;

  rect.x = (int)_positionX;
  rect.y = (int)_positionY;
  rect.w = 20;
  rect.h = 20;

  SDL_RenderFillRect(lePinceau, &rect);
}

void Balle::monter() { _positionY += 1; }

void Balle::avancer(double dt) {
  _positionX += _vitesseX * dt;
  _positionY += _vitesseY * dt;
}

bool Balle::sortGauche() const {
  if (_positionX < 0) {
    return true;
  }
  return false;
}

bool Balle::sortDroite() const {
  if (_positionX + 20 > LARGEUR_FENETRE * 5) {
    return true;
  }
  return false;
}

void Balle::getY() const {
  cout << _positionY << endl;
}

bool Balle::toucheRaquette(const Raquette &raquette) const {
  if (_positionX + 20 >= raquette.getX() && (_positionX <= raquette.getX() + 20) && (_positionY + 20 >= raquette.getY()) && (_positionY <= raquette.getY() + 120)) {
    return true;
  }

  return false;
}

void Balle::rebondir(const Raquette &raquette) {
  if (_vitesseX > 0) {
    // Si la balle allait vers la DROITE, on la colle à GAUCHE de la raquette
    _positionX = raquette.getX() - 20;
  } else {
    // Si la balle allait vers la GAUCHE, on la colle à DROITE de la raquette
    _positionX = raquette.getX() + 20;
  }

  _vitesseX *= -1.2;

  float midBalle = _positionY + 10;
  float midRaquette = raquette.getY() + 60;

  float diff = midBalle - midRaquette;

  _vitesseY = diff * 5;
}

void Balle::rebondMurs() {
  if (_positionY < 0) {
    _vitesseY *= -1.2;
  }
  if (_positionY > HAUTEUR_FENETRE * 5 - 20) {
    _vitesseY *= -1;
  }
}

void Balle::reinitialiser() {
  // 1. On remet au centre (formules du main)
  _positionX = (LARGEUR_FENETRE * 5) / 2;
  _positionY = (HAUTEUR_FENETRE * 5) / 2;

  // 2. On remet la vitesse de base
  if (rand() % 2 == 0) {
    _vitesseX = 300;
  } else {
    _vitesseX = -300;
  }
  _vitesseY = (rand() % 400) - 100;
}