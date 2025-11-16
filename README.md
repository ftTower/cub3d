# 🎮 Cub3D

<div align="center">

**Un moteur de rendu 3D inspiré de Wolfenstein 3D**

*Projet développé dans le cadre du cursus 42 Paris*

[![42 Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=flat-square)](https://github.com/42Paris/minilibx-linux)

</div>

---

## 📖 À propos

**Cub3D** est un moteur 3D basé sur la technique du **raycasting**, la même technologie utilisée dans le légendaire Wolfenstein 3D. Ce projet transforme une carte 2D en une expérience immersive en 3D grâce à une gestion dynamique des collisions et à l'application de textures personnalisées.

Le raycasting simule une vue 3D en lançant des rayons depuis la position du joueur pour calculer les distances aux murs, créant ainsi une illusion de profondeur sans nécessiter de réel moteur 3D.

![Cub3D Gameplay](https://github.com/ftTower/cub3d/blob/main/assets/gamePic.png)

---

## 📑 Table des matières

- [Fonctionnalités](#-fonctionnalités)
- [Technologies](#-technologies)
- [Installation](#-installation)
- [Utilisation](#-utilisation)
- [Commandes](#-commandes)
- [Configuration](#-configuration)
- [Architecture du projet](#-architecture-du-projet)
- [Auteurs](#-auteurs)

---

## ✨ Fonctionnalités

### Rendu graphique
- ⚡ **Raycasting en temps réel** : Génère une vue 3D fluide à partir d'une carte 2D
- 🎨 **Système de textures** : Application de textures personnalisées pour chaque direction (Nord, Sud, Est, Ouest)
- 🌈 **Couleurs configurables** : Sol et plafond personnalisables via RGB

### Gameplay
- 🎯 **Détection de collisions** : Système de collision précis pour une navigation réaliste
- 🧭 **Navigation fluide** : Déplacements et rotations optimisés
- 🗺️ **Mini-carte interactive** : Affichage de la position du joueur en temps réel

### Outils de développement
- 🐛 **Mode Debug (F3)** : Affiche les informations de débogage (FPS, position, direction)
- 🔍 **Zoom dynamique** : Contrôle du niveau de zoom sur la mini-carte
- 📊 **Affichage des performances** : Suivi en temps réel des performances

![Cub3D Map View](https://github.com/ftTower/cub3d/blob/main/assets/mapPic.png)

---

## 🛠️ Technologies

- **Langage** : C (Norme 42)
- **Bibliothèque graphique** : [MiniLibX](https://github.com/42Paris/minilibx-linux)
- **Build system** : GNU Make
- **Compilation** : GCC avec flags `-Wall -Wextra -Werror`
- **Mathématiques** : Bibliothèque math.h pour les calculs trigonométriques

---

## 📥 Installation

### Prérequis

Assurez-vous d'avoir les dépendances suivantes installées sur votre système Linux :

```bash
# Compilateur C
sudo apt-get install gcc make

# Dépendances MiniLibX
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

### Compilation

```bash
# Cloner le dépôt
git clone https://github.com/ftTower/Cub3D.git
cd Cub3D

# Compiler MiniLibX
make minlibx

# Compiler le projet
make

# Lancer le programme avec une carte
./cub3d maps/VanGogh.cub
```

### Compilation bonus

```bash
make bonus  # Compile avec les fonctionnalités bonus (si disponibles)
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et l'exécutable
make re     # Recompile complètement le projet
```

---

## 🎮 Utilisation

### Lancement rapide

```bash
./cub3d <chemin_vers_carte.cub>
```

### Exemples

```bash
# Carte Van Gogh (recommandée)
./cub3d maps/VanGogh.cub

# Carte basique
./cub3d maps/file.cub
```

---

## ⌨️ Commandes

### Déplacements
| Touche | Action |
|--------|--------|
| `W` / `↑` | Avancer |
| `S` / `↓` | Reculer |
| `A` | Déplacement latéral gauche |
| `D` | Déplacement latéral droit |

### Rotation
| Touche | Action |
|--------|--------|
| `←` | Rotation à gauche |
| `→` | Rotation à droite |

### Interface
| Touche | Action |
|--------|--------|
| `M` | Afficher/Masquer la mini-carte |
| `F3` | Activer/Désactiver le mode debug |
| `+` | Zoomer sur la mini-carte |
| `-` | Dézoomer sur la mini-carte |
| `ESC` | Quitter le programme |

![Cub3D Debug Mode](https://github.com/ftTower/cub3d/blob/main/assets/debugPic.png)

---

## ⚙️ Configuration

### Format du fichier .cub

Le fichier de configuration définit l'environnement du jeu. Il doit contenir :

#### 1. Textures des murs
```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
```

#### 2. Couleurs (format RGB)
```
F 220,100,0    # Floor (Sol)
C 225,30,0     # Ceiling (Plafond)
```

#### 3. Carte
```
111111111111
100000000001
101100000001
100000N00001
111111111111
```

### Caractères de la carte
- `0` : Espace vide (navigable)
- `1` : Mur
- `N` / `S` / `E` / `W` : Position et orientation de départ du joueur
  - **N** : Nord
  - **S** : Sud
  - **E** : Est
  - **W** : Ouest

### Règles de validation
- ✅ La carte doit être entourée de murs (`1`)
- ✅ Un seul joueur doit être présent
- ✅ Tous les chemins de textures doivent être valides
- ✅ Les couleurs doivent être au format RGB (0-255)
- ✅ Les espaces vides doivent être fermés (pas d'ouverture vers le vide)

### Exemple de fichier

Voir l'exemple complet : [VanGogh.cub](https://github.com/ftTower/cub3d/blob/main/maps/VanGogh.cub)

```bash
NO ./maps/textures/VanGogh/north.xpm
SO ./maps/textures/VanGogh/south.xpm
WE ./maps/textures/VanGogh/west.xpm
EA ./maps/textures/VanGogh/east.xpm

F 184,113,39
C 51,153,255

111111111111111111111111
100000000011000000000001
101100000111000000000001
100100000000000000000001
111111111011000001110001
100000000011000001110001
111111111111111111111111
```

---

## 🏗️ Architecture du projet

```
cub3d/
├── src/                    # Code source principal
│   ├── init/              # Initialisation et parsing
│   │   ├── config.c       # Parsing de la configuration
│   │   ├── map.c          # Parsing de la carte
│   │   └── map_parse.c    # Validation de la carte
│   ├── raycasting/        # Moteur de rendu
│   │   ├── raycasting.c   # Algorithme DDA
│   │   ├── textures.c     # Gestion des textures
│   │   └── raytures.c     # Application des textures
│   ├── loop/              # Boucle de jeu
│   │   ├── game.c         # Boucle principale
│   │   └── key.c          # Gestion des événements
│   ├── img/               # Gestion graphique
│   │   ├── img.c          # Manipulation d'images
│   │   ├── drawing.c      # Fonctions de dessin
│   │   └── put_string.c   # Affichage de texte
│   ├── main.c             # Point d'entrée
│   ├── free.c / free2.c   # Gestion de la mémoire
│   └── utils.c / utils2.c # Fonctions utilitaires
├── ReFile/                 # Bibliothèque de parsing
│   ├── gnl/               # Get Next Line
│   └── src/               # Utilitaires de fichiers
├── includes/              # Headers
│   └── cub3d.h           # Définitions et structures
├── maps/                  # Cartes de test
│   └── textures/         # Textures XPM
├── assets/                # Ressources (captures d'écran)
└── Makefile              # Compilation

```

### Concepts clés implémentés

- **Digital Differential Analyzer (DDA)** : Algorithme de raycasting pour détecter les intersections
- **Gestion mémoire** : Allocation et libération propre des ressources
- **Event loop** : Boucle de rendu et gestion des événements MiniLibX
- **Texture mapping** : Projection de textures 2D sur les murs
- **Collision detection** : Détection des collisions avec les murs

---

## 👥 Auteurs

Développé par [@ftTower](https://github.com/ftTower)

---

<div align="center">

**⭐ Si ce projet vous a plu, n'hésitez pas à lui donner une étoile ! ⭐**

</div>


