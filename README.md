# Cub3D

Cub3D est un moteur 3D basé sur la technique du raycasting, développé dans le cadre du projet 42 Paris. Il permet de transformer une carte 2D en une expérience immersive en 3D grâce à une gestion dynamique des collisions et à l'application de textures.

![Cub3D](https://github.com/ftTower/cub3d/blob/main/assets/gamePic.png)

## Table des matières

- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Configuration](#configuration)

![Cub3D](https://github.com/ftTower/cub3d/blob/main/assets/mapPic.png)

## Fonctionnalités

- **Raycasting** : Génère une vue 3D à partir d'une carte 2D.
- **Gestion des collisions** : Détecte et gère dynamiquement les collisions pour une navigation réaliste.
- **Textures** : Applique des textures aux murs et surfaces pour renforcer l'immersion.
- **Navigation fluide** : Déplacement et rotation optimisés via le clavier (et éventuellement la souris).

## Installation

### Prérequis

- Un compilateur C (gcc, clang, etc.)
- La bibliothèque [MiniLibX](https://github.com/42Paris/minilibx-linux) (ou la version adaptée à votre système)
- [Make](https://www.gnu.org/software/make/)


### utilisation
   ```bash
   git clone https://github.com/ftTower/Cub3D.git
   cd Cub3D && make minlibx && make
   ./cub3d maps/VanGogh.cub
  ```

![Cub3D](https://github.com/ftTower/cub3d/blob/main/assets/debugPic.png)
# Commandes de base
- **Déplacement** : Utilisez les touches directionnelles ou les touches W, A, S, D.
- **Rotation** : Contrôlez la rotation via les flèches gauche/droite.
- **Quitter** : Appuyez sur ESC pour sortir du programme.
- **Carte** : Appuyez sur **M** pour afficher la carte.
- **Mode Debug** : Appuyez sur **F3** pour activer ou désactiver le mode debug.
- **Zoomer** : Appuyez sur **+** pour zoomer.
- **Dézoomer** : Appuyez sur **-** pour dézoomer.

# Configuration
Le fichier de configuration (extension .cub) doit définir :

- **Textures** : Chemins vers les fichiers de texture pour chaque mur (Nord, Sud, Est, Ouest).
- **Couleurs** : Définition des couleurs pour le sol et le plafond.
- **Carte** : La représentation 2D de la carte, où 1 représente un mur et 0 un espace libre.

voir exemple ci dessous : 
[VanGogh.cub](https://github.com/ftTower/cub3d/blob/main/maps/VanGogh.cub)


