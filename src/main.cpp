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
  Balle balle((LARGEUR_FENETRE * 5) / 2, (HAUTEUR_FENETRE * 5) / 2, 300, 0);
  Raquette joueur1(10, 20);
  Raquette joueur2(LARGEUR_FENETRE * 5 - 30, 10);

  bool quitter = false;
  bool hautJ1 = false;
  bool basJ1 = false;
  bool hautJ2 = false;
  bool basJ2 = false;
  int scoreJ1 = 0;
  int scoreJ2 = 0;

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
        hautJ2 = true;
        break;
        case HAUT_RELACHE:
        hautJ2 = false;
        break;
      case BAS_APPUYE:
        basJ2 = true;
        break;
      case BAS_RELACHE:
        basJ2 = false;
        break;
        case Z_APPUYE:
          hautJ1 = true;
          break;
        case Z_RELACHE:
          hautJ1 = false;
          break;
        case S_APPUYE:
          basJ1 = true;
          break;
        case S_RELACHE:
          basJ1 = false;
          break;
      default:
        break;
      }

      evenement = moteur.evenementRecu();
    }

    // II. Mise à jour de l'état du jeu

    double dt = moteur.getDeltaTime();

    if (hautJ1) {
      if (joueur1.peutMonter()) {
        joueur1.monter(dt);
      }
      //cout << joueur1.getY() << endl;
    }

    if (hautJ2) {
      if (joueur2.peutMonter()) {
        joueur2.monter(dt);
      }
      //cout << joueur2.getY() << endl;
    }

    if (basJ1) {
      if (joueur1.peutDescendre()) {
        joueur1.descendre(dt);
      }
      //cout << joueur1.getY() << endl;
    }

    if (basJ2) {
      if (joueur2.peutDescendre()) {
        joueur2.descendre(dt);
      }
      //cout << joueur2.getY() << endl;
    }

    if (balle.toucheRaquette(joueur2)) {
      balle.rebondir(joueur2);
    }

    if (balle.toucheRaquette(joueur1)) {
      balle.rebondir(joueur1);
    }

    balle.avancer(dt);
    balle.rebondMurs();

    // III. Generation de l'image à afficher

    moteur.initialiserRendu(); // efface ce qui avait ete affiche precedemment
                               // et reinitalise en ecran noir

    // TODO: afficher vos personnages, objets, etc.

    balle.afficher(moteur.getRenderer());
    joueur1.afficher(moteur.getRenderer());
    joueur2.afficher(moteur.getRenderer());

    if (scoreJ1 != 5 && scoreJ2 != 5) {
      if (balle.sortGauche()) {
        scoreJ2++;
        cout << "t sortie bro " << scoreJ1 << ":" << scoreJ2 << endl;
        moteur.attendre(0.5);
        balle.reinitialiser();
      }

      if (balle.sortDroite()) {
        scoreJ1++;
        cout << "c dommage tu perds : " << scoreJ1 << ":" << scoreJ2 << endl;
        moteur.attendre(0.5);
        balle.reinitialiser();
      }
    } else {
      cout << "c'est finito " << scoreJ1 << ":" << scoreJ2 << endl;
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
