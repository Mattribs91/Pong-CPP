#include <SDL_image.h>

#include "Moteur.h"

Moteur::Moteur(const std::string &nomDuJeu, int fps) {
  // On lance le moteur
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;

  // Sous-bibliotheque SDL_image qui permet de charger du PNG
  if (IMG_Init(IMG_INIT_PNG) == 0)
    std::cerr << "IMG_Init failed: " << SDL_GetError() << std::endl;

  // Creation de la fenetre
  _window = SDL_CreateWindow(
      nomDuJeu.c_str(), // Le titre de la fenetre
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, // Centree en hauteur/largeur
      LARGEUR_FENETRE * ECHELLE, HAUTEUR_FENETRE * ECHELLE, // Taille
      SDL_WINDOW_RESIZABLE); // On peut changer la taille de la fenetre
  if (!_window)
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;

  // Creation du renderer (qui gere l'affichage)
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (!_renderer)
    std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;

  // On ne fait pas d'interpolation pour garder l'aspect "pixel art"
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

  _temps = SDL_GetTicks();
  _ancienTemps = 0;
  _fps = fps;
}

Moteur::~Moteur() {
  IMG_Quit();
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void Moteur::initialiserRendu() {
  Uint32 tempsActuel = SDL_GetTicks();
  // Si c'est la premiere frame, on initialise _ancienTemps
  if (_ancienTemps == 0) {
    _ancienTemps = tempsActuel;
  }

  _deltaTime = (tempsActuel - _ancienTemps) / 1000.0;
  _ancienTemps = tempsActuel;

  _startFrame = tempsActuel;
  // On remplie la fenetre avec du noir
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
}

void Moteur::finaliserRendu() {
  SDL_RenderPresent(_renderer);

  Uint32 endFrame = SDL_GetTicks();
  Uint32 frameDuration = endFrame - _startFrame;
  Uint32 desiredDuration = 1000 / _fps;

  if (frameDuration < desiredDuration) {
    SDL_Delay(desiredDuration - frameDuration);
  }
}

Evenement Moteur::evenementRecu() const {
  SDL_Event ev;
  while (SDL_PollEvent(&ev) == 1) {
    if (ev.type == SDL_QUIT)
      return QUITTER_APPUYE;
    if (ev.type == SDL_KEYDOWN) {
      if (ev.key.keysym.sym == SDLK_SPACE)
        return ESPACE_APPUYE;
      if (ev.key.keysym.sym == SDLK_UP)
        return HAUT_APPUYE;
      if (ev.key.keysym.sym == SDLK_RIGHT)
        return DROITE_APPUYE;
      if (ev.key.keysym.sym == SDLK_LEFT)
        return GAUCHE_APPUYE;
      if (ev.key.keysym.sym == SDLK_DOWN)
        return BAS_APPUYE;
      if (ev.key.keysym.sym == SDLK_ESCAPE)
        return QUITTER_APPUYE;
      if (ev.key.keysym.sym == SDLK_z)
        return Z_APPUYE;
      if (ev.key.keysym.sym == SDLK_q)
        return Q_APPUYE;
      if (ev.key.keysym.sym == SDLK_s)
        return S_APPUYE;
      if (ev.key.keysym.sym == SDLK_d)
        return D_APPUYE;
    } else if (ev.type == SDL_KEYUP) {
      if (ev.key.keysym.sym == SDLK_SPACE)
        return ESPACE_RELACHE;
      if (ev.key.keysym.sym == SDLK_UP)
        return HAUT_RELACHE;
      if (ev.key.keysym.sym == SDLK_RIGHT)
        return DROITE_RELACHE;
      if (ev.key.keysym.sym == SDLK_LEFT)
        return GAUCHE_RELACHE;
      if (ev.key.keysym.sym == SDLK_DOWN)
        return BAS_RELACHE;
      if (ev.key.keysym.sym == SDLK_ESCAPE)
        return QUITTER_RELACHE;
      if (ev.key.keysym.sym == SDLK_z)
        return Z_RELACHE;
      if (ev.key.keysym.sym == SDLK_q)
        return Q_RELACHE;
      if (ev.key.keysym.sym == SDLK_s)
        return S_RELACHE;
      if (ev.key.keysym.sym == SDLK_d)
        return D_RELACHE;
    }
  }
  return AUCUN;
}

bool Moteur::animationsAmettreAjour() {
  int duree_image_ms = 1000 / _fps;
  int nouveau_temps = SDL_GetTicks();
  if (nouveau_temps - _temps >= duree_image_ms) {
    _temps = nouveau_temps;
    return true;
  }
  // else
  return false;
}

void Moteur::attendre(double secondes) const {
  SDL_Delay(int(secondes * 1000));
}

SDL_Renderer *Moteur::getRenderer() { return _renderer; }

double Moteur::getDeltaTime() const { return _deltaTime; }
