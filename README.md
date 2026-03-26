_This project has been created as part of the 42 curriculum by demane, rbourdon._

# cub3D

## Description

`cub3D` is a small first-person 3D engine written in C with MiniLibX, inspired by the original Wolfenstein 3D raycasting approach.

The goal is to render a dynamic view of a maze from the player point of view by:

- parsing a `.cub` scene file,
- validating textures, colors, and map consistency,
- running a real-time raycaster,
- handling player inputs and collisions,
- drawing floor/ceiling colors and wall textures per orientation.

This repository contains both the mandatory part and several bonus features implemented in the same project.

## Features

### Mandatory features

- Raycasting-based 3D rendering.
- 4 wall textures depending on wall orientation (North/South/West/East).
- Floor and ceiling RGB colors.
- Keyboard movement with `W`, `A`, `S`, `D`.
- Camera rotation with left/right arrow keys.
- Clean exit on `ESC` and window close button.
- Robust parsing with explicit error messages.

### Bonus features implemented

- Wall collisions.
- Minimap overlay.
- Doors that can open/close.
- Animated sprites (torch in world, weapon HUD animation).
- Mouse-based camera rotation.

## Instructions

### Requirements

- Linux environment with X11 development libraries.
- `cc` compiler.
- `make`.

Important note: in the original 42 project skeleton, MiniLibX is not provided by default.
You must download it first, then extract/copy it at the project root as `minilibx-linux/`.

This repository already includes a local `minilibx-linux/` folder, but if it is missing on your machine, set it up before running `make`.

### MiniLibX setup (if missing)

1. Download the Linux MiniLibX archive from your 42 resources.
2. Extract it.
3. Place the extracted folder at the root of this project and name it `minilibx-linux`.

Expected tree:

```text
cub3D/
  minilibx-linux/
  includes/
  srcs/
  Makefile
```

### Build

```bash
make
```

Other useful rules:

```bash
make clean
make fclean
make re
```

### Run

```bash
./cub3D maps/simple.cub
```

The program expects exactly one argument: a valid `.cub` map file.

## Controls

- `W` / `A` / `S` / `D`: move.
- `Left Arrow` / `Right Arrow`: rotate camera.
- `Mouse`: rotate camera (when enabled).
- `L`: toggle mouse control.
- `E`: open/close door in front of the player.
- `Left Click`: trigger weapon animation.
- `Left Shift`: temporary movement speed boost.
- `ESC`: quit cleanly.
- Window close button: quit cleanly.

## Map Format

### Mandatory identifiers

- `NO path_to_north_texture.xpm`
- `SO path_to_south_texture.xpm`
- `WE path_to_west_texture.xpm`
- `EA path_to_east_texture.xpm`
- `F R,G,B`
- `C R,G,B`

### Extended identifier used in this project

- `D path_to_door_texture.xpm` (required only if door tiles are present)

### Map characters

- Mandatory set: `0`, `1`, `N`, `S`, `E`, `W`, and spaces.
- Extended set used for bonus: `D` (door), `T` (torch sprite).

### Validation highlights

- `.cub` extension required for scene file.
- Exactly one player spawn (`N`/`S`/`E`/`W`).
- Map must be closed by walls.
- RGB values must be in `[0, 255]`.
- Texture files must be `.xpm` and accessible.
- In this implementation, parsed texture dimensions are validated to `64x64`.

## Project Structure

- `srcs/parser/`: file parsing and map validation.
- `srcs/init/`: MLX init and global cleanup.
- `srcs/raycaster/`: ray setup, DDA, wall projection, draw.
- `srcs/textures/`: texture loading and texture sampling.
- `srcs/hooks/`: keyboard/mouse events, movement, frame loop.
- `srcs/minimap/`: minimap rendering.
- `srcs/sprites/`: weapon and torch animations/sprite drawing.
- `includes/`: headers and shared structures.
- `maps/`: sample scenes.

## Error Handling and Memory

- Invalid configuration exits with `Error\n` and an explicit message.
- Parsing errors free allocated parser/game resources.
- Runtime shutdown destroys MLX images/windows/display and frees heap allocations.

## Resources

### Raycasting and graphics references

- Lode Vandevenne, Raycasting tutorial:
  - https://lodev.org/cgtutor/raycasting.html
- MiniLibX references:
  - https://harm-smits.github.io/42docs/libs/minilibx
  - `man mlx` (depending on local setup)
- 42 subject and peer evaluation documents.

### How AI was used in this project

AI assistance was used for support tasks only, such as:

- documenting architecture and preparing technical summaries,
- rephrasing explanations and improving README clarity,
- checking consistency between implemented features and expected project requirements.

All implementation choices, code behavior, and final validation were manually reviewed and understood by project contributors.
