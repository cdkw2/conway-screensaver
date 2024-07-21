#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ALIVE '&'
#define DEAD ' '

int WIDTH, HEIGHT;

void init_grid(char **grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = (rand() % 5 == 0) ? ALIVE : DEAD;
        }
    }
}

void print_grid(char **grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mvaddch(y, x, grid[y][x]);
        }
    }
    refresh();
}

int count_neighbors(char **grid, int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + WIDTH) % WIDTH;
            int ny = (y + dy + HEIGHT) % HEIGHT;
            if (grid[ny][nx] == ALIVE) count++;
        }
    }
    return count;
}

void update_grid(char **grid, char **new_grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = count_neighbors(grid, x, y);
            if (grid[y][x] == ALIVE) {
                new_grid[y][x] = (neighbors == 2 || neighbors == 3) ? ALIVE : DEAD;
            } else {
                new_grid[y][x] = (neighbors == 3) ? ALIVE : DEAD;
            }
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = new_grid[y][x];
        }
    }
}

int main() {
    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);

    getmaxyx(stdscr, HEIGHT, WIDTH);

    char **grid = malloc(HEIGHT * sizeof(char *));
    char **new_grid = malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        grid[i] = malloc(WIDTH * sizeof(char));
        new_grid[i] = malloc(WIDTH * sizeof(char));
    }

    init_grid(grid);

    while (1) {
        print_grid(grid);
        update_grid(grid, new_grid);


        if (getch() == 'q') break;

        usleep(100000);
    }

    for (int i = 0; i < HEIGHT; i++) {
        free(grid[i]);
        free(new_grid[i]);
    }
    free(grid);
    free(new_grid);

    endwin();
    return 0;
}
