#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define MAX_AGE 5
#define CELL_CHAR "&"
#define GLIDER_INTERVAL 3

int WIDTH, HEIGHT;
int infinite_mode = 0;
time_t last_glider_time;

typedef struct {
    int alive;
    int age;
} Cell;

void init_grid(Cell **grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x].alive = (rand() % 5 == 0);
            grid[y][x].age = 0;
        }
    }
}

void print_grid(Cell **grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x].alive) {
                int color = grid[y][x].age % MAX_AGE + 1;
                attron(COLOR_PAIR(color));
                mvaddstr(y, x, CELL_CHAR);
                attroff(COLOR_PAIR(color));
            } else {
                mvaddch(y, x, ' ');
            }
        }
    }
    refresh();
}

int count_neighbors(Cell **grid, int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + WIDTH) % WIDTH;
            int ny = (y + dy + HEIGHT) % HEIGHT;
            if (grid[ny][nx].alive) count++;
        }
    }
    return count;
}

void spawn_glider(Cell **grid, int x, int y) {
    int glider[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };
    
    for (int dy = 0; dy < 3; dy++) {
        for (int dx = 0; dx < 3; dx++) {
            int nx = (x + dx) % WIDTH;
            int ny = (y + dy) % HEIGHT;
            grid[ny][nx].alive = glider[dy][dx];
            grid[ny][nx].age = 0;
        }
    }
}

void update_grid(Cell **grid, Cell **new_grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = count_neighbors(grid, x, y);
            if (grid[y][x].alive) {
                new_grid[y][x].alive = (neighbors == 2 || neighbors == 3);
                new_grid[y][x].age = new_grid[y][x].alive ? grid[y][x].age + 1 : 0;
            } else {
                new_grid[y][x].alive = (neighbors == 3);
                new_grid[y][x].age = 0;
            }
        }
    }
    
    if (infinite_mode && difftime(time(NULL), last_glider_time) >= GLIDER_INTERVAL) {
        int rx = rand() % WIDTH;
        int ry = rand() % HEIGHT;
        spawn_glider(new_grid, rx, ry);
        last_glider_time = time(NULL);
    }
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = new_grid[y][x];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--infinite") == 0) {
        infinite_mode = 1;
    }

    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_CYAN, -1);
    init_pair(5, COLOR_BLUE, -1);

    getmaxyx(stdscr, HEIGHT, WIDTH);
    Cell **grid = malloc(HEIGHT * sizeof(Cell *));
    Cell **new_grid = malloc(HEIGHT * sizeof(Cell *));
    for (int i = 0; i < HEIGHT; i++) {
        grid[i] = malloc(WIDTH * sizeof(Cell));
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
    }

    init_grid(grid);
    last_glider_time = time(NULL);

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
