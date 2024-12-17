#include <string.h>
#include <math.h>

#define AOC_IMPLEMENTATION
#include "aoc.h"

#define INPUT_FILE "src/input/input08.txt"

#define WIDTH 12
#define HEIGHT 12
#define MAX_ANTENNA_COUNT 64

typedef struct {
    int x;
    int y;
} antenna_t;

typedef struct {
    antenna_t data[MAX_ANTENNA_COUNT];
    int count;
} antenna_arr_t;

int main() {
    char *input = NULL;
    long file_size = read_input(INPUT_FILE, &input);
    if (file_size == -1) {
        printf("Error reading input file\n");
        return 1;
    }

    char **buffer;
    array2d_from_input(WIDTH, HEIGHT, input, file_size, &buffer);

    map_t(char, antenna_arr_t) antenna_map;
    map_init(&antenna_map, NULL, NULL);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (buffer[y][x] != '.') {
                antenna_arr_t *val = map_get(&antenna_map, buffer[y][x]);
                if (val) {
                    (*val).data[(*val).count++] = (antenna_t) { .x = x, .y = y };
                } else {
                    antenna_arr_t new_antenna_arr;
                    new_antenna_arr.count = 0;
                    new_antenna_arr.data[new_antenna_arr.count++] = (antenna_t) { .x = x, .y = y };
                    map_set(&antenna_map, buffer[y][x], new_antenna_arr);
                }
            }
        }
    }

    int key;
    map_iter_t iter = map_iter(&antenna_map);

    int silver = 0;
    bool visited_silver[HEIGHT][WIDTH] = { false };

    // Calc silver
    while (map_next(&antenna_map, &iter, &key)) {
        antenna_arr_t *curr_type = map_get(&antenna_map, key);
        if (curr_type->count < 2) continue;
        for (int i = 0; i < curr_type->count; i++) {
            for (int j = i + 1; j < curr_type->count; j++) {
                int x1 = 2 * curr_type->data[i].x - curr_type->data[j].x;
                int y1 = 2 * curr_type->data[i].y - curr_type->data[j].y;

                int x2 = 2 * curr_type->data[j].x - curr_type->data[i].x;
                int y2 = 2 * curr_type->data[j].y - curr_type->data[i].y;

                if (is_in_bounds(x1, y1, WIDTH, HEIGHT) && !visited_silver[y1][x1]) {
                    visited_silver[y1][x1] = true;
                    silver++;
                }

                if (is_in_bounds(x2, y2, WIDTH, HEIGHT) && !visited_silver[y2][x2]) {
                    visited_silver[y2][x2] = true;
                    silver++;
                }
            }
        }
    }

    int gold = 0;
    iter = map_iter(&antenna_map);
    bool visited_gold[HEIGHT][WIDTH] = { false };

    // Calc gold
    while (map_next(&antenna_map, &iter, &key)) {
        antenna_arr_t *curr_type = map_get(&antenna_map, key);
        if (curr_type->count < 2) continue;

        for (int i = 0; i < curr_type->count; i++) {
            for (int j = i + 1; j < curr_type->count; j++) {
                int dx = curr_type->data[i].x - curr_type->data[j].x;
                int dy = curr_type->data[i].y - curr_type->data[j].y;

                int buff_x = curr_type->data[i].x;
                int buff_y = curr_type->data[i].y;
                
                while (is_in_bounds(buff_x, buff_y, WIDTH, HEIGHT)) {
                    if (!visited_gold[buff_y][buff_x]) {
                        visited_gold[buff_y][buff_x] = true;
                        gold++;
                    }
                    buff_x += dx;
                    buff_y += dy;
                }

                buff_x = curr_type->data[j].x;
                buff_y = curr_type->data[j].y;

                while (is_in_bounds(buff_x, buff_y, WIDTH, HEIGHT)) {
                    if (!visited_gold[buff_y][buff_x]) {
                        visited_gold[buff_y][buff_x] = true;
                        gold++;
                    }
                    buff_x -= dx;
                    buff_y -= dy;
                }
            }
        }
    }

    map_delete(&antenna_map);
    array2d_free(&buffer, HEIGHT);

    printf("--------- DAY 08 ---------\n");
    printf("Silver result is %d\n", silver);
    printf("Gold result is %d\n", gold);
    printf("--------------------------\n");
    return 0;
}