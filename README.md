
# Conway's Game of Life (Terminal saver)

This project is an enhanced implementation of Conway's Game of Life, a cellular automaton simulation, using the ncurses library in C. It now includes a configuration file system for easy customization.

## Features

- Dynamic grid size that adjusts to the terminal window
- Randomly initialized starting state with configurable density
- Toroidal (wrapping) or bounded grid edges
- Real-time visualization using ncurses
- Color representation of cell age (optional)
- Infinite mode with periodic glider spawning
- Customizable cell character
- Adjustable update speed
- Configuration file for easy customization

## Requirements

- C compiler (e.g., gcc)
- ncurses library
- UNIX-like operating system (Linux, macOS, etc.)

## Usage

Compile and run the program with these commands:
```
gcc -o conway conway.c -lncurses
chmod +x conway
./conway
```
The simulation will start automatically. Press 'q' to quit the program, or 'r' to reset the grid.
Make a alias on your .bashrc or whatever file to run it anywhere.

## Configuration

The program uses a configuration file named `game_of_life.conf`in same directory. Explanation of each configuration variable:

- `infinite_mode`: (0 or 1) Enables or disables infinite mode.
- `update_interval`: (microseconds) Controls the speed of the simulation.
- `cell_char`: The character used to represent live cells.
- `max_age`: The maximum age of a cell, used for color cycling.
- `color_mode`: (0 or 1) Enables or disables color representation of cell age.
- `glider_interval`: (seconds) The time interval between glider spawns in infinite mode.
- `initial_density`: (0.0 to 1.0) The probability of a cell being alive in the initial state.
- `wrap_edges`: (0 or 1) Enables toroidal grid edges when set to 1, or bounded edges when set to 0.

Example `game_of_life.conf`:

```
infinite_mode=1
update_interval=100000
cell_char=#
max_age=8
color_mode=1
glider_interval=5
initial_density=0.3
wrap_edges=1
```

## Infinite Mode

In infinite mode, the simulation prevents equilibrium by introducing glider patterns at the specified interval, creating an ongoing screensaver and preventing the grid from settling into a static state.

## Future Ideas

- [x] Making this infinite to prevent endless loops of same actions
- [x] Using unicode characters instead of "&"
- [x] Letting user control parameters like cell character, update speed, colors, etc.
- [x] Adding colors
- [x] Config file system
- [ ] Others...
