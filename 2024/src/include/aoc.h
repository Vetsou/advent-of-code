#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Libraries
#include <cmap.h>

int DIRS[8][2] = {
    { 0,  1},
    { 0, -1},
    { 1,  0},
    {-1,  0},
    { 1,  1},
    { 1, -1},
    {-1,  1},
    {-1, -1}
};

int CARDINAL_DIRS[4][2] = {
    { 0,  1},
    { 0, -1},
    { 1,  0},
    {-1,  0} 
};

int CROSS_DIRS[4][2] = {
    { 1,  1},
    {-1, -1}, 
    { 1, -1},
    {-1,  1},
};


// Checks if (x,y) is within (width, height) rect
bool is_in_bounds(int x, int y, int width, int height);

// Reads file filename and saves the result into 'data_buffer'
int read_input(const char *filename, char **data_buffer);

// Generates a 2d array from AoC string input
int array2d_from_input(
    int width,
    int height,
    const char *input,
    long input_len,
    char ***buffer
);

// Frees the 2d array
void array2d_free(char ***buffer, int height);

#ifdef AOC_IMPLEMENTATION

bool is_in_bounds(int x, int y, int width, int height) {
    return x >= width || x < 0 || y >= height || y < 0;
}

int read_input(const char *filename, char **data_buffer) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *data_buffer = malloc(file_size + 1);
    if (!*data_buffer) {
        perror("Error allocating memory");
        fclose(file);
        return -1;
    }

    fread(*data_buffer, 1, file_size, file);
    (*data_buffer)[file_size] = '\0';

    fclose(file);
    return file_size;
}

int array2d_from_input(
    int width,
    int height,
    const char *input,
    long input_len,
    char ***buffer
) {
    *buffer = (char**)malloc(sizeof(char*) * height);
    if (*buffer == NULL) {
        perror("Failed to allocate array2d rows");
        return -1;
    }

    for (int i = 0; i < height; i++) {
        (*buffer)[i] = malloc(sizeof(char) * width);

        if ((*buffer)[i] == NULL) {
            perror("Failed to allocate array2d columns");
            for (int j = 0; j < i; j++) free((*buffer)[j]);
            free(*buffer);
            return -1;
        }
    }

    int y = 0, x = 0;
    for (long i = 0; i < input_len; i++) {
        if (input[i] == '\r' || input[i] == '\n') continue;
        (*buffer)[y][x++] = input[i];

        if (x == width) { x = 0; y++; }
        if (y == height) break;
    }
    return 0;
}

void array2d_free(char ***buffer, int height) {
    for (int i = 0; i < height; i++) free((*buffer)[i]);
    free((*buffer));
}

#endif // AOC_IMPLEMENTATION

#endif // AOC_H