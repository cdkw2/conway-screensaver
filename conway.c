#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define CONFIG_FILE "game_of_life.conf"
#define MAX_COLORS 8

int WIDTH, HEIGHT;
time_t last_glider_time;

typedef struct {
    int alive;
    int age;
} Cell;

typedef struct {
    int infinite_mode;
    int update_interval;
    char cell_char[8];
    int max_age;
    int color_mode;
    int glider_interval;
    float initial_density;
    int wrap_edges;
} Config;

Config config;

void load_config() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        config.infinite_mode = 0;
        config.update_interval = 100000;
        strcpy(config.cell_char, "&");
        config.max_age = 5;
        config.color_mode = 1;
        config.glider_interval = 3;
        config.initial_density = 0.2;
        config.wrap_edges = 1;
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");
        if (key && value) {
            if (strcmp(key, "infinite_mode") == 0) config.infinite_mode = atoi(value);
            else if (strcmp(key, "update_interval") == 0) config.update_interval = atoi(value);
            else if (strcmp(key, "cell_char") == 0) strncpy(config.cell_char, value, 7);
            else if (strcmp(key, "max_age") == 0) config.max_age = atoi(value);
            else if (strcmp(key, "color_mode") == 0) config.color_mode = atoi(value);
            else if (strcmp(key, "glider_interval") == 0) config.glider_interval = atoi(value);
            else if (strcmp(key, "initial_density") == 0) config.initial_density = atof(value);
            else if (strcmp(key, "wrap_edges") == 0) config.wrap_edges = atoi(value);
        }
    }

    fclose(file);
}

void init_grid(Cell **grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x].alive = (rand() / (float)RAND_MAX < config.initial_density);
            grid[y][x].age = 0;
        }
    }
}

void print_grid(Cell **grid) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x].alive) {
                if (config.color_mode) {
                    int color = (grid[y][x].age % config.max_age) + 1;
                    attron(COLOR_PAIR(color));
                    mvaddstr(y, x, config.cell_char);
                    attroff(COLOR_PAIR(color));
                } else {
                    mvaddstr(y, x, config.cell_char);
                }
            } else {
                mvaddch(y, x, ' ');
            }
        }
    }
}

int count_neighbors(Cell **grid, int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (config.wrap_edges) {
                nx = (nx + WIDTH) % WIDTH;
                ny = (ny + HEIGHT) % HEIGHT;
            } else {
                if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT) continue;
            }
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
    
    if (config.infinite_mode && difftime(time(NULL), last_glider_time) >= config.glider_interval) {
        int rx = rand() % WIDTH;
        int ry = rand() % HEIGHT;
        spawn_glider(new_grid, rx, ry);
        last_glider_time = time(NULL);
    }
}

int main() {
    load_config();
    
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);
    start_color();
    use_default_colors();

    for (int i = 1; i <= MAX_COLORS; i++) {
        init_pair(i, i, -1);
    }

    getmaxyx(stdscr, HEIGHT, WIDTH);
    
    Cell **grid = malloc(HEIGHT * sizeof(Cell *));
    Cell **new_grid = malloc(HEIGHT * sizeof(Cell *));
    for (int i = 0; i < HEIGHT; i++) {
        grid[i] = malloc(WIDTH * sizeof(Cell));
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
    }
    
    init_grid(grid);
    last_glider_time = time(NULL);
    
    int generation = 0;
    while (1) {
        print_grid(grid);
        mvprintw(HEIGHT, 0, "Generation: %d | Press 'q' to quit, 'r' to reset", generation);
        refresh();

        update_grid(grid, new_grid);

        Cell **temp = grid;
        grid = new_grid;
        new_grid = temp;

        generation++;

        int ch = getch();
        if (ch == 'q') break;
        else if (ch == 'r') {
            init_grid(grid);
            generation = 0;
        }
        usleep(config.update_interval);
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
