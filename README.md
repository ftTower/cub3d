# Cub3D

Cub3D est un moteur 3D basé sur la technique du raycasting, développé dans le cadre du projet 42 Paris. Il permet de transformer une carte 2D en une expérience immersive en 3D grâce à une gestion dynamique des collisions et à l'application de textures.

## Table des matières

- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Configuration](#configuration)
- [Contributions](#contributions)
- [Crédits](#crédits)
- [Licence](#licence)

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

### installation
   ```bash
   git clone https://github.com/ftTower/Cub3D.git
   cd Cub3D && make minilibx && make
   ./cub3d maps/VanGogh.cub
  ```
   
