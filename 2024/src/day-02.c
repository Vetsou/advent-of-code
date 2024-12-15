#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define AOC_IMPLEMENTATION
#include "aoc.h"

#define LVL_MAX_LEN 16
#define INPUT_FILE "src/input/input02.txt"

bool is_safe(int levels[], int len) {
    bool asc = true, desc = true;

    for (int i = 0; i < len - 1; i++) {
        int diff = abs(levels[i] - levels[i + 1]);

        if (diff < 1 || diff > 3) return false;
        if (levels[i] < levels[i + 1]) desc = false;
        if (levels[i] > levels[i + 1]) asc = false;
    }

    return asc || desc;
}

int is_dampener_safe(int levels[], const int len) {
    int *temp = (int *)malloc((len - 1) * sizeof(int));

    for (int i = 0; i < len; i++) {
        int index = 0;

        for (int j = 0; j < len; j++) {
            if (j == i) continue;
            temp[index++] = levels[j];
        }

        if (is_safe(temp, len - 1)) {
            free(temp);
            return 1;
        }
    }

    free(temp);
    return 0;
}

int main() {
    char *input = NULL;
    long file_size = read_input(INPUT_FILE, &input);
    if (file_size == -1) {
        printf("Error reading input file\n");
        return 1;
    }

    int safe_reports = 0;
    int dampener_safe_reports = 0;
    
    char *line = strtok(input, "\n");
    char *lvl_buffer;

    while (line != NULL) {
        char *level_str = strtok_s(line, " ", &lvl_buffer);
        int levels[LVL_MAX_LEN];
        int lvl_len = 0;

        while (level_str != NULL) {
            levels[lvl_len++] = atoi(level_str);
            level_str = strtok_s(NULL, " ", &lvl_buffer);
        }

        if (is_safe(levels, lvl_len)) safe_reports++;
        if (is_dampener_safe(levels, lvl_len)) dampener_safe_reports++;

        line = strtok(NULL, "\r\n");
    }

    printf("--------- DAY 02 ---------\n");
    printf("Silver result is %d\n", safe_reports);
    printf("Gold result is %d\n", dampener_safe_reports);
    printf("--------------------------\n");

    free(input);
    return 0;
}