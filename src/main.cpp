#include <vector>

#include "Balle.h"
#include "Image.h"
#include "Moteur.h"
#include "Raquette.h"

using namespace std;

int main(int, char **) // Version special du main, ne pas modifier
{
  // Initialisation du jeu
  Moteur moteur("Pong", 600);

  // TODO: charger images, creer personnages, etc.
  Balle balle((LARGEUR_FENETRE * 5) / 2, (HAUTEUR_FENETRE * 5) / 2);
  Raquette joueur1(10, 10);
  Raquette joueur2(LARGEUR_FENETRE * 5 - 30, 10);

  int positionBalleX = 20;
  int positionBalleY = 20;

  bool quitter = false;

  // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
  // (en general, 60 fois par seconde)
  while (!quitter) {
    // I. Gestion des evenements
    Evenement evenement = moteur.evenementRecu();
    while (evenement != AUCUN) {
      switch (evenement) {
      // QUITTER = croix de la fenetre ou Echap
      case QUITTER_APPUYE:
        quitter = true;
        break;
      case HAUT_APPUYE:
        joueur1.monter();
        break;
      case BAS_APPUYE:
        joueur1.descendre();
        break;
      default:
        break;
      }

      evenement = moteur.evenementRecu();
    }

    // II. Mise à jour de l'état du jeu

    // TODO: faire bouger vos personnages, etc.
    balle.droite();

    // III. Generation de l'image à afficher

    moteur.initialiserRendu(); // efface ce qui avait ete affiche precedemment
                               // et reinitalise en ecran noir

    // TODO: afficher vos personnages, objets, etc.

    balle.afficher(moteur.getRenderer());
    joueur1.afficher(moteur.getRenderer());
    joueur2.afficher(moteur.getRenderer());

    if (balle.toucheMur()) {
      cout << "t sortie bro" << endl;
      quitter = true;
    }

    /*
      Affiche l'image en se cadencant sur la frequence de
      rafraichissement de l'ecran (donc va en general mettre le
      programme en pause jusqu'a ce que l'ecran soit rafraichi). En
      general, 60 images fois par seconde, mais ca peut dependre du
      materiel
    */
    moteur.finaliserRendu();
  }

  return 0;
}
