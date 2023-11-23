#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// algo shamelessly borrowed from https://cefns.nau.edu/%7Epek7/CS200/Project%209.pdf

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

void init_maze(int w, int h, char *grid) {
    for (int i=0; i < w * h; i++) {
        grid[i] = '#';
    }
}

int xy_to_flat(int x, int y, int w) {
    return y * w + x;
}

int in_bounds(int x, int y, int w, int h) {
    if (x < 0 || x >= w) {
        return 0;
    }
    if (y < 0 || y >= h){
        return 0;
    }
    return 1;
}

void visit(int x, int y, char *grid, int w, int h) {
    grid[xy_to_flat(x, y, w)] = '.';
    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;
    for (int i = 0; i < 4; i++) {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }
    for (int i = 0; i < 4; i++) {
        int dx = 0;
        int dy = 0;
        switch (dirs[i]) {
            case NORTH:
                dy = -1;
                break;
            case SOUTH:
                dy = 1;
                break;
            case EAST:
                dx = 1;
                break;
            case WEST:
                dx = -1;
                break;
        }
        int x2 = x + (dx<<1);
        int y2 = y + (dy<<1);
        if (in_bounds(x2, y2, w, h)) {
            if (grid[xy_to_flat(x2, y2, w)] == '#') {
                grid[xy_to_flat(x2 - dx, y2 - dy, w) ] = '.';
                visit(x2, y2, grid, w, h);
            }
        }
    }
}

int main(int argc, char **argv) {
    int w = 13;
    int h = 13;
    char grid[w * h];
    srand(time(0));
    init_maze(w, h, grid);
    visit(1, 1, grid, w, h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf("%c", (char)grid[xy_to_flat(x, y, w)]);
        }
        printf("\n");
    }
    return 0;
}
