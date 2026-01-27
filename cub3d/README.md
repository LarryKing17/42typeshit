# cub3D

A simple Wolfenstein-style raycasting project (42 school) written in C using MiniLibX.

This repository implements a 2.5D renderer that reads a `.cub` scene file (textures, floor/ceiling colors and a map grid) and displays a real-time first-person view with basic movement and view rotation.

This project was created as part of the 42 curriculum by shvalma and alrighi_.

## Features
- Raycasting-based 3D view (wall projection)
- XPM textures for walls (NO / SO / WE / EA)
- Floor and ceiling color support
- Player placement detection in the map
- Keyboard controls for movement and rotation

## Build
The project uses the included `makefile`. To compile with the default resolution:

```bash
make
```

You can override the window size with environment variables used by other forks (not required here). The project default is WIDTH=1200 and HEIGHT=800 (see `include/cub3d.h`).

Clean and rebuild:

```bash
make clean
make fclean
make re
```

Notes:
- The MiniLibX (Linux) used by the project is included in the `mlx/` folder. The makefile will build it automatically.
- Compiler: the `makefile` uses `cc` with `-Wall -Wextra -Werror -g` and includes `include` and `libft`.

## Run

Run the compiled executable with a `.cub` map file:

```bash
./cub3D maps/test.cub
```

The program will open a window and render the scene described in the `.cub` file.

## Controls

Movement and view controls are implemented via keyboard events (X11 keycodes were used):

- W (keycode 119): Move forward
- S (keycode 115): Move backward
- A (keycode 97): Move left (strafe)
- D (keycode 100): Move right (strafe)
- Left Arrow (keycode 65361): Rotate left
- Right Arrow (keycode 65363): Rotate right
- ESC (keycode 65307): Exit the program

The player movement performs basic collision with map walls.

## .cub file format

A `.cub` configuration file contains a header (texture paths and floor/ceiling colors) followed by the map grid. Header lines accepted by the parser:

- `NO <path>` — north wall texture (XPM)
- `SO <path>` — south wall texture (XPM)
- `WE <path>` — west wall texture (XPM)
- `EA <path>` — east wall texture (XPM)
- `F R,G,B` — floor color (three integers 0–255 separated by commas)
- `C R,G,B` — ceiling color (three integers 0–255 separated by commas)

After header entries, the map grid follows. The parser expects the map to be closed (surrounded by walls) and to contain exactly one player start position. Example player characters: `N`, `S`, `E`, `W` (direction the player faces). Map tiles:

- `1` — wall
- `0` — empty space
- `N`, `S`, `E`, `W` — player start position and facing direction

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
- `include/` — project headers (`cub3d.h`)
- `maps/` — example `.cub` files
- `mlx/` — MiniLibX for Linux (library and sources)
- `libft/` — utility functions used by the project

## Notes & Tips

- Textures must be valid XPM files. The parser validates that texture paths end with `.xpm`.
- Colors must be three comma-separated integers from 0 to 255.
- The map must be properly enclosed by walls and contain exactly one player start.
- If the program fails to load textures or parse the map, it prints an error and exits.

## Credits

Authors: shvalma and alrighi_ (42 curriculum project)

This README was generated/updated to document the `cub3D` raycasting project.
