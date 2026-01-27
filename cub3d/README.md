
# _This project has been created as part of the 42 curriculum by zvalenti, idridi.

## Description

`cub3D` is a Wolfenstein-style 2.5D raycasting project written in C using the MiniLibX library. The program parses a `.cub` scene file that contains texture paths, floor and ceiling colors, and a 2D map grid. It renders a first-person view using raycasting (wall projection), supports textured walls, and allows the player to move and rotate inside the map with simple collision detection.

The goal is to implement the fundamentals of raycasting, 2D map parsing, texture mapping, and basic user interaction using a minimal graphics library.

## Instructions

Compilation

Build the project with the provided `makefile`:

```bash
make
```

This will compile the program and the included MiniLibX (Linux) in `mlx/` and produce the executable `cub3D`.

Cleanings

```bash
make clean    # remove object files
make fclean   # remove object files and the executable
make re       # rebuild (fclean + all)
```

Execution

Run the executable with a `.cub` map file:

```bash
./cub3D maps/test.cub
```

Window size / resolution

Default window size is defined in `include/cub3d.h` as `WIDTH = 1200` and `HEIGHT = 800`. Modify those constants if you want a different resolution and recompile.

Required arguments

The program expects exactly one argument: the path to a `.cub` map file. If the argument is missing or the map is invalid the program exits with an error.

## Features

- Raycasting-based 3D view with textured walls
- XPM textures for the four wall directions (NO / SO / WE / EA)
- Floor and ceiling color support (RGB)
- Player detection and simple collision handling
- Keyboard controls for movement and rotation

## Controls

- W (keycode 119): Move forward
- S (keycode 115): Move backward
- A (keycode 97): Strafe left
- D (keycode 100): Strafe right
- Left Arrow (keycode 65361): Rotate left
- Right Arrow (keycode 65363): Rotate right
- ESC (keycode 65307): Exit

Controls are implemented with X11 keycodes via MiniLibX.

## .cub file format

A `.cub` file is composed of a header followed by a map grid. The parser recognizes the following header entries (order not strict, empty lines allowed between header lines):

- `NO <path>` — north wall texture (XPM)
- `SO <path>` — south wall texture (XPM)
- `WE <path>` — west wall texture (XPM)
- `EA <path>` — east wall texture (XPM)
- `F R,G,B` — floor color (three integers 0–255 separated by commas)
- `C R,G,B` — ceiling color (three integers 0–255 separated by commas)

After the header the map grid follows. The map must be closed by walls (`1`) and contain a single player start position using one of `N`, `S`, `E`, or `W` which also encodes the initial facing direction.

Map tiles:

- `1` — wall
- `0` — empty space
- `N`, `S`, `E`, `W` — player start position and facing

Example (`maps/test.cub`):

```
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

C 35,19,73
F 15,6,40

1111111111111111111
10W1001001001000001
1011000001000001001
1001001001111101111
1001111000001001001
1000000000000001001
1001111111111001001
1111000000000001011
1000000001000000001
1111111111111111111
```

## Project structure

- `src/` — source files (raycasting, drawing, parsing, main)
- `include/` — project header (`cub3d.h`)
- `maps/` — example `.cub` files
- `mlx/` — MiniLibX implementation for Linux (library + sources)
- `libft/` — utility library used by the project

## Resources

Background reading and tutorials that are useful for this project:

- Lode Vandevenne — "A Trip to the Center of the Pixel" (raycasting tutorial)
- "Raycasting in C" tutorials and blog posts (search for Wolfenstein raycaster tutorials)
- MiniLibX documentation and examples (see `mlx/` folder)
- X11 programming references for keycodes on Linux

AI usage

An AI assistant was used to help draft and structure this README file only. The AI was responsible for:

- Creating this README content (structure, explanations, usage examples)
- Suggesting clarifications for build and run instructions

No code logic or project source files were modified by the AI assistant as part of this README update; only documentation text was produced/edited.

## Notes & Tips

- Textures must be valid XPM files and paths must end with `.xpm`.
- Colors must be specified as three integers between 0 and 255, separated by commas.
- Ensure the map is closed by walls and contains exactly one player start.
- If textures fail to load the program exits with an error message.

## Credits

Authors: shvalma, alrighi_

