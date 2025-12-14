# 🎮 Cub3D

<div align="center">

**A 3D rendering engine inspired by Wolfenstein 3D**

*Project developed as part of the 42 Paris curriculum*

[![42 Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=flat-square)](https://github.com/42Paris/minilibx-linux)

</div>

---

## 📖 About

**Cub3D** is a 3D engine based on the **raycasting** technique, the same technology used in the legendary Wolfenstein 3D. This project transforms a 2D map into an immersive 3D experience through dynamic collision management and custom texture application.

Raycasting simulates a 3D view by casting rays from the player's position to calculate distances to walls, creating an illusion of depth without requiring a real 3D engine.

![Cub3D Gameplay](https://github.com/ftTower/cub3d/blob/main/assets/gamePic.png)

---

## 📑 Table of Contents

- [Features](#-features)
- [Technologies](#-technologies)
- [Installation](#-installation)
- [Usage](#-usage)
- [Controls](#-controls)
- [Configuration](#-configuration)
- [Project Architecture](#-project-architecture)
- [Authors](#-authors)

---

## ✨ Features

### Graphics Rendering
- ⚡ **Real-time Raycasting**: Generates a smooth 3D view from a 2D map
- 🎨 **Texture System**: Custom texture application for each direction (North, South, East, West)
- 🌈 **Configurable Colors**: Customizable floor and ceiling via RGB

### Gameplay
- 🎯 **Collision Detection**: Precise collision system for realistic navigation
- 🧭 **Smooth Navigation**: Optimized movement and rotation
- 🗺️ **Interactive Mini-map**: Real-time player position display

### Development Tools
- 🐛 **Debug Mode (F3)**: Displays debugging information (FPS, position, direction)
- 🔍 **Dynamic Zoom**: Mini-map zoom level control
- 📊 **Performance Display**: Real-time performance monitoring

![Cub3D Map View](https://github.com/ftTower/cub3d/blob/main/assets/mapPic.png)

---

## 🛠️ Technologies

- **Language**: C (42 Standard)
- **Graphics Library**: [MiniLibX](https://github.com/42Paris/minilibx-linux)
- **Build System**: GNU Make
- **Compilation**: GCC with flags `-Wall -Wextra -Werror`
- **Mathematics**: math.h library for trigonometric calculations

---

## 📥 Installation

### Prerequisites

Make sure you have the following dependencies installed on your Linux system:

```bash
# C Compiler
sudo apt-get install gcc make

# MiniLibX Dependencies
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

### Compilation

```bash
# Clone the repository
git clone https://github.com/ftTower/Cub3D.git
cd Cub3D

# Compile MiniLibX
make minlibx

# Compile the project
make

# Run the program with a map
./cub3d maps/VanGogh.cub
```

### Bonus Compilation

```bash
make bonus  # Compile with bonus features (if available)
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Fully recompile the project
```

---

## 🎮 Usage

### Quick Start

```bash
./cub3d <path_to_map.cub>
```

### Examples

```bash
# Van Gogh Map (recommended)
./cub3d maps/VanGogh.cub

# Basic Map
./cub3d maps/file.cub
```

---

## ⌨️ Controls

### Movement
| Key | Action |
|--------|--------|
| `W` / `↑` | Move Forward |
| `S` / `↓` | Move Backward |
| `A` | Strafe Left |
| `D` | Strafe Right |

### Rotation
| Key | Action |
|--------|--------|
| `←` | Rotate Left |
| `→` | Rotate Right |

### Interface
| Key | Action |
|--------|--------|
| `M` | Show/Hide Mini-map |
| `F3` | Enable/Disable Debug Mode |
| `+` | Zoom In Mini-map |
| `-` | Zoom Out Mini-map |
| `ESC` | Exit Program |

![Cub3D Debug Mode](https://github.com/ftTower/cub3d/blob/main/assets/debugPic.png)

---

## ⚙️ Configuration

### .cub File Format

The configuration file defines the game environment. It must contain:

#### 1. Wall Textures
```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
```

#### 2. Colors (RGB format)
```
F 220,100,0    # Floor
C 225,30,0     # Ceiling
```

#### 3. Map
```
111111111111
100000000001
101100000001
100000N00001
111111111111
```

### Map Characters
- `0`: Empty space (navigable)
- `1`: Wall
- `N` / `S` / `E` / `W`: Player starting position and orientation
  - **N**: North
  - **S**: South
  - **E**: East
  - **W**: West

### Validation Rules
- ✅ The map must be surrounded by walls (`1`)
- ✅ Only one player must be present
- ✅ All texture paths must be valid
- ✅ Colors must be in RGB format (0-255)
- ✅ Empty spaces must be closed (no openings to the void)

### Example File

See full example: [VanGogh.cub](https://github.com/ftTower/cub3d/blob/main/maps/VanGogh.cub)

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

## 🏗️ Project Architecture

```
cub3d/
├── src/                    # Main source code
│   ├── init/              # Initialization and parsing
│   │   ├── config.c       # Configuration parsing
│   │   ├── map.c          # Map parsing
│   │   └── map_parse.c    # Map validation
│   ├── raycasting/        # Rendering engine
│   │   ├── raycasting.c   # DDA Algorithm
│   │   ├── textures.c     # Texture management
│   │   └── raytures.c     # Texture application
│   ├── loop/              # Game loop
│   │   ├── game.c         # Main loop
│   │   └── key.c          # Event handling
│   ├── img/               # Graphics management
│   │   ├── img.c          # Image manipulation
│   │   ├── drawing.c      # Drawing functions
│   │   └── put_string.c   # Text display
│   ├── main.c             # Entry point
│   ├── free.c / free2.c   # Memory management
│   └── utils.c / utils2.c # Utility functions
├── ReFile/                 # Parsing library
│   ├── gnl/               # Get Next Line
│   └── src/               # File utilities
├── includes/              # Headers
│   └── cub3d.h           # Definitions and structures
├── maps/                  # Test maps
│   └── textures/         # XPM Textures
├── assets/                # Resources (screenshots)
└── Makefile              # Compilation

```

### Key Implemented Concepts

- **Digital Differential Analyzer (DDA)**: Raycasting algorithm for intersection detection
- **Memory Management**: Clean allocation and deallocation of resources
- **Event Loop**: Rendering loop and MiniLibX event handling
- **Texture Mapping**: Projection of 2D textures onto walls
- **Collision Detection**: Wall collision detection

---

## 👥 Authors

Developed by [@ftTower](https://github.com/ftTower)

---

<div align="center">

**⭐ If you liked this project, feel free to give it a star! ⭐**

</div>


