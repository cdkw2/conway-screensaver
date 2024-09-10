# Conway's Game of Life (Terminal Screensaver)

![conway](assets/conway-screensaver.gif)

This project is an enhanced implementation of Conway's Game of Life, a cellular automaton simulation, using the ncurses library in C. It now includes a configuration file system for easy customization.

## Features

- **Dynamic Grid Size**: Automatically adjusts to the terminal window dimensions.
- **Random Initialization**: The starting state is randomly generated with a configurable density of live cells.
- **Grid Edges**: Supports both toroidal (wrapping) and bounded edges.
- **Real-Time Visualization**: Utilizes ncurses for smooth updates and rendering.
- **Color Representation**: Optionally displays cell age using different colors.
- **Infinite Mode**: Introduces periodic glider patterns to maintain activity on the grid.
- **Customizable Cell Character**: Users can define which character represents live cells.
- **Adjustable Update Speed**: The speed of the simulation can be modified.
- **Configuration File**: A dedicated file (`game_of_life.conf`) allows for easy customization of settings.

## Requirements

- A C compiler (e.g., gcc)
- The ncurses library
- A UNIX-like operating system (Linux, macOS, etc.)

## Usage

To compile and run the program, execute the following commands:

```bash
git clone https://github.com/cdkw2/conway-screensaver
cd conway-screensaver/
make
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

In infinite mode, the simulation continuously introduces glider patterns at specified intervals, preventing the grid from reaching a static state and ensuring ongoing activity.

## Future Ideas

- [x] User controls for parameters like cell character, update speed, and colors.
- [x] Additional features and optimizations to enhance user experience.
- [x] Optimize the grid update logic to handle larger grids more efficiently. 

This project offers a fun and interactive way to explore cellular automata through a terminal interface, making it not just a screensaver but also a tool for learning about complex systems.

Version 1.0.0
