# Conway's Game of Life Screensaver

This project is an implementation of Conway's Game of Life, a cellular automaton simulation, using the ncurses library in C.

## Features

- A dynamic grid size that adjusts to the terminal window
- Randomly initialized starting state
- Toroidal (wrapping) grid edges
- Real-time visualization using ncurses
- Color representation of cell age
- Infinite mode with periodic glider spawning

## Requirements

- C compiler (e.g., gcc)
- ncurses library
- UNIX-like operating system (Linux, macOS, etc.)

## Usage

To compile the program, use the following command:
```
gcc -o conway conway.c -lncurses
```
Run the program with:
```
./conway
```
For infinite mode with periodic glider spawning:
```
./conway --infinite
```

The simulation will start automatically. Press 'q' to quit the program.

## Code Structure

- `init_grid`: Initializes the grid with a random state
- `print_grid`: Displays the current state of the grid
- `count_neighbors`: Counts the number of live neighbors for a given cell
- `spawn_glider`: Introduces a glider pattern at a given location (used in infinite mode)
- `update_grid`: Applies the rules of the Game of Life to update the grid
- `main`: Sets up ncurses, manages memory allocation, and runs the main game loop

## Infinite Mode

In infinite mode, the simulation prevents equilibrium by introducing glider patterns ever like 3 seconds creating ongoing screensaver and preventing the grid from getting into a static state.

## Future Ideas

- [x] Making this infinite to prevent endless loops of same actions
- [ ] Using unicode characters instead of "&"
- [ ] Letting user control parameters like cell character, update speed, colors, etc.
- [x] Adding colors
- [ ] Others...
