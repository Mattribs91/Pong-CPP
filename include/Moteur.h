#ifndef MOTEUR_H
#define MOTEUR_H

#include <iostream>

#include <SDL.h>

const int TAILLE_CASE = 16; // Cases de 16 pixels de cote

const int NB_CASE_LARGEUR = 10;
const int NB_CASE_HAUTEUR = 8;

const int LARGEUR_FENETRE = TAILLE_CASE * NB_CASE_LARGEUR;
const int HAUTEUR_FENETRE = TAILLE_CASE * NB_CASE_HAUTEUR;

// Les images sont en "pixel art", elles sont toutes petites.  Pour
// que ca s'affiche bien, on multiplie tout par une echelle de 5.
// L'univers du jeu se passe dans 160x120 pixel, mais la fenetre fera
// 5*160x5*128pixels.
const int ECHELLE = 5;

// Les differents types d'evenements disponibles
enum Evenement {
  AUCUN,
  GAUCHE_APPUYE,
  GAUCHE_RELACHE,
  DROITE_APPUYE,
  DROITE_RELACHE,
  HAUT_APPUYE,
  HAUT_RELACHE,
  BAS_APPUYE,
  BAS_RELACHE,
  ESPACE_APPUYE,
  ESPACE_RELACHE,
  QUITTER_APPUYE,
  QUITTER_RELACHE,

  Z_APPUYE,
  Z_RELACHE,
  Q_APPUYE,
  Q_RELACHE,
  S_APPUYE,
  S_RELACHE,
  D_APPUYE,
  D_RELACHE
};

class Moteur {
  // Structures internes de la SDL
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  int _fps;
  int _temps;
  Uint32 _startFrame;
  Uint32 _ancienTemps;
  double _deltaTime;

public:
  // Constructeur qui initialise le moteur, la fenetre, etc.
  // Par defaut la fenetre fait 160 x 128 pixels (grossi 5 fois pour
  // l'affichage)
  // -> l'univers de jeu se fait sur 160 x 128 pixels (c'est arbitraire),
  //    soit une grille de 10x8 cases de 16 pixels de côté
  // L'argument FPS permet de regler la vitesse des animations
  // (8 FPS = 8 images par seconde)
  Moteur(const std::string &nomDuJeu, int fps);

  // Destructeur qui ferme le moteur et libere la memoire
  ~Moteur();

  // Initalise l'image par un ecran noir
  void initialiserRendu();

  // Finalise l'image et l'envoie a la carte graphique pour affichage sur
  // l'ecran
  void finaliserRendu();

  // Renvoie le dernier evenement recu (AUCUN si rien n'est recu)
  Evenement evenementRecu() const;

  // Renvoie true s'il faut mettre a jour les animations
  bool animationsAmettreAjour();

  // Renvoie le temps ecoule depuis la derniere image (en secondes)
  double getDeltaTime() const;

  // Met le jeu en pause pendant un certain nombre de secondes
  // (ATTENTION : le jeu ne répond plus lorsqu'il est en pause,
  // les evenements ne seront traites qu'apres la pause)
  void attendre(double secondes) const;

  // (Pour un usage interne, vous n'aurez jamais besoin de cette methode.)
  SDL_Renderer *getRenderer();
};

#endif // MOTEUR_H
