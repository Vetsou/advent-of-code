#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define AOC_IMPLEMENTATION
#include "aoc.h"

#define INPUT_FILE "src/input/input03.txt"

bool is_num(char c) {
    return c >= '0' && c <= '9';
}

void consume_do(char** ptr, bool* new_state) {
    if (strncmp(*ptr, "do()", 4) == 0) {
        *new_state = true;
        *ptr += 4;
    }

    if (strncmp(*ptr, "don't()", 7) == 0) {
        *new_state = false;
        *ptr += 7;
    }
}

bool consume_nums(char** ptr, int* result) {
    char *num_start = *ptr;

    while (is_num(**ptr)) (*ptr)++;
    if (**ptr == '\0') return false;

    int *val1 = (int*)malloc(sizeof(int));
    *val1 = atoi(num_start);

    if (**ptr != ',') {
        free(val1);
        return false;
    }
    (*ptr)++;

    num_start = *ptr;

    while (is_num(**ptr)) (*ptr)++;
    if (**ptr != ')') {
        free(val1);
        return false;
    }

    int *val2 = (int*)malloc(sizeof(int));
    *val2 = atoi(num_start);

    *result = (*val1) * (*val2);

    free(val1);
    free(val2);
    return true;
}

bool consume_mul(char** ptr) {
    if (strncmp(*ptr, "mul(", 4) == 0) {
        *ptr += 4;
        return true;
    }

    return false;
}

int silver(char* input) {
    int sum = 0;
    char *ptr = input;

    while (*ptr != '\0') {
        if (*ptr == 'm') {
            if (consume_mul(&ptr)) {
                int result;
                if (consume_nums(&ptr, &result)) sum += result;
            }
        }
        ptr++;
    }
    return sum;
}

int gold(char* input) {
    bool do_enable = true;
    int sum = 0;
    char *ptr = input;

    while (*ptr != '\0') {
        if (*ptr == 'd') consume_do(&ptr, &do_enable);

        if (*ptr == 'm' && do_enable) {
            if (consume_mul(&ptr)) {
                int result;
                if (consume_nums(&ptr, &result)) sum += result;
            }
        }
        ptr++;
    }

    return sum;
}

int main() {
    char *input = NULL;
    long file_size = read_input(INPUT_FILE, &input);
    if (file_size == -1) {
        printf("Error reading input file\n");
        return 1;
    }

    printf("--------- DAY 03 ---------\n");
    printf("Silver result is %d\n", silver(input));
    printf("Gold result is %d\n", gold(input));
    printf("--------------------------\n");
    return 0;
}