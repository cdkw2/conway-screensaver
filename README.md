# Conway's Game of Life Screensaver

This project is an implementation of Conway's Game of Life, a cellular automaton simulation, using the ncurses library in C.

## This implementation features:

-   A dynamic grid size that adjusts to the terminal window
-   Randomly initialized starting state
-   Toroidal (wrapping) grid edges (def intented)
-   Real-time visualization using ncurses

## Requirements

-   C compiler (e.g., gcc)
-   ncurses library
-   UNIX-like operating system (Linux, macOS, etc.)
## Usage:


To compile the program, use the following command:
``
gcc -o conway conway.c -lncurses
``

Run the program with 
``./conway``

The simulation will start automatically. Press 'q' to quit the program.

## Code Structure

-   `init_grid`: Initializes the grid with a random state
-   `print_grid`: Displays the current state of the grid
-   `count_neighbors`: Counts the number of live neighbors for a given cell
-   `update_grid`: Applies the rules of the Game of Life to update the grid
-   `main`: Sets up ncurses, manages memory allocation, and runs the main game loop

## Future ideas:

- [ ] Making this infinite because it gets to an endless loop of same actions after a while
- [ ] Using unicode instead of "&"
- [ ] Letting user give control like the character to choose, time between actions, color and etc
- [*] Adding colors
- [ ] Others...
