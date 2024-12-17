#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Libraries
#include <cmap.h>

const int DIRS[8][2] = {
    { 0,  1},
    { 0, -1},
    { 1,  0},
    {-1,  0},
    { 1,  1},
    { 1, -1},
    {-1,  1},
    {-1, -1}
};

const int CARDINAL_DIRS[4][2] = {
    { 0,  1},
    { 0, -1},
    { 1,  0},
    {-1,  0} 
};

const int CROSS_DIRS[4][2] = {
    { 1,  1},
    {-1, -1}, 
    { 1, -1},
    {-1,  1},
};


// Checks if (x,y) is within (width, height) rect
bool is_in_bounds(int x, int y, int width, int height);

// Reads file filename and saves the result into 'data_buffer'
int read_input(const char *filename, char **data_buffer);

// Splits the 'str' by 'delim'. Returns the number of slices in 'count'.
char** split_string(
    const char* str,
    const char* delim_list,
    int* count,
    int max_count
);

// Frees the split_str ptr and the elements it contains.
void free_split_str(char **split_str, int count);

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

// Allocates a new array of ints created from 'str_arr'.
int* str_array_to_int_array(char **str_arr, int count);

// Allocates a new array of ints created from 'str_arr'.
uint64_t* str_array_to_int64_array(char **str_arr, int count);





#ifdef AOC_IMPLEMENTATION

bool is_in_bounds(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
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

char** split_string(
    const char* str,
    const char* delim_list,
    int* count,
    int max_count
) {
    char* copy = strdup(str);
    char** tokens = malloc(sizeof(char*) * max_count);

    *count = 0;
    char *tok_buff;

    char* token = strtok_s(copy, delim_list, &tok_buff);
    while (token && *count < max_count) {
        tokens[*count] = strdup(token);
        (*count)++;
        token = strtok_s(NULL, delim_list, &tok_buff);
    }

    free(copy);
    return tokens;
}

void free_split_str(char **split_str, int count) {
    for (int i = 0; i < count; i++) free(split_str[i]);
    free(split_str);
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

int* str_array_to_int_array(char **str_arr, int count) {
    int *int_arr = (int *)malloc(sizeof(*int_arr) * count);

    for (int i = 0; i < count; i++) int_arr[i] = atoi(str_arr[i]);
    return int_arr;
}

uint64_t* str_array_to_int64_array(char **str_arr, int count) {
    uint64_t *int_arr = (uint64_t *)malloc(sizeof(*int_arr) * count);

    for (int i = 0; i < count; i++) int_arr[i] = atoll(str_arr[i]);
    return int_arr;
}

#endif // AOC_IMPLEMENTATION
#endif // AOC_H