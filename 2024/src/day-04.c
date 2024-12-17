#include <string.h>

#define AOC_IMPLEMENTATION
#include "aoc.h"

#define WIDTH 10
#define HEIGHT 10
#define XMAS_LEN 4
#define INPUT_FILE "src/input/input04.txt"

bool is_outside_bounds(int x, int y) {
    return x >= WIDTH || x < 0 || y >= HEIGHT || y < 0;
}

int check_xmas(int x, int y, int x_dir, int y_dir, char **data) {
    const char *xmas_word = "XMAS";

    for (int i = 0; i < XMAS_LEN; i++) {
        int new_x = x + i * x_dir;
        int new_y = y + i * y_dir;

        if (is_outside_bounds(new_x, new_y)) {
            return 0;
        }

        if (data[new_y][new_x] != xmas_word[i]) return 0;
    }

    return 1;
}

int check_mas(int x, int y, char **data) {
    for (int i = 0; i < 4; i += 2) {
        int x_dir1 = x + CROSS_DIRS[i][0];
        int y_dir1 = y + CROSS_DIRS[i][1];

        int x_dir2 = x + CROSS_DIRS[i + 1][0];
        int y_dir2 = y + CROSS_DIRS[i + 1][1];

        if (is_outside_bounds(x_dir1, y_dir1) || is_outside_bounds(x_dir2, y_dir2)) {
            return 0;
        }

        char lett1 = data[y_dir1][x_dir1];
        char lett2 = data[y_dir2][x_dir2];

        if ((lett1 == 'S' && lett2 == 'M') || (lett2 == 'S' && lett1 == 'M')) continue;
        return 0;
    }
    return 1;
}

int silver() {
    char *input = NULL;
    long file_size = read_input(INPUT_FILE, &input);
    if (file_size == -1) {
        printf("Error reading input file\n");
        return 1;
    }

    char **data_array;
    array2d_from_input(WIDTH, HEIGHT, input, file_size, &data_array);

    int sum = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (data_array[y][x] == 'X') {
                for (int d = 0; d < 8; d++) {
                    sum += check_xmas(x, y, DIRS[d][0], DIRS[d][1], data_array);
                }
            }
        }
    }

    array2d_free(&data_array, HEIGHT);
    return sum;
}

int gold() {
    char *input = NULL;
    long file_size = read_input(INPUT_FILE, &input);
    if (file_size == -1) {
        printf("Error reading input file\n");
        return 1;
    }

    char **data_array;
    array2d_from_input(WIDTH, HEIGHT, input, file_size, &data_array);

    int sum = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (data_array[y][x] == 'A') {
                sum += check_mas(x, y, data_array);
            }
        }
    }

    array2d_free(&data_array, HEIGHT);
    return sum;
}

int main() {
    printf("--------- DAY 04 ---------\n");
    printf("Silver result is %d\n", silver());
    printf("Gold result is %d\n", gold());
    printf("--------------------------\n");
    return 0;
}