#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_COUNT 6
#define INPUT_FILE "src/input/input01.txt"

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int silver() {
    FILE *file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("Error reading file\n");
        return -1;
    }

    int list_1[NUM_COUNT];
    int list_2[NUM_COUNT];
    char line[32];

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        char *part1 = strtok(line, "   ");
        char *part2 = strtok(NULL, "   ");
        
        if (part1 && part2) {
            list_1[i] = atoi(part1);
            list_2[i] = atoi(part2);
        } else {
            printf("Malformed line: %s", line);
            fclose(file);
            return -1;
        }
        i++;
    }

    fclose(file);

    qsort(list_1, NUM_COUNT, sizeof(int), compare_ints);
    qsort(list_2, NUM_COUNT, sizeof(int), compare_ints);

    int sum = 0;
    for (i = 0; i < NUM_COUNT; i++) {
        sum += abs(list_1[i] - list_2[i]);
    }

    return sum;
}

int gold() {
    FILE *file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("Error reading file\n");
        return -1;
    }

    // Simulate a map as max value is 99999 and map is <int, int>
    int sim_map[100000] = {0};

    int list_1[NUM_COUNT];
    char line[32];

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        char *part1 = strtok(line, "   ");
        char *part2 = strtok(NULL, "   ");
        
        if (part1 && part2) {
            list_1[i] = atoi(part1);
            int value2 = atoi(part2);
            sim_map[value2]++;
        } else {
            printf("Malformed line: %s", line);
            fclose(file);
            return -1;
        }
        i++;
    }

    fclose(file);

    int sum = 0;
    for (i = 0; i < NUM_COUNT; i++) {
        int val = list_1[i];
        sum += val * sim_map[val];
    }

    return sum;
}

int main() {
    printf("--------- DAY 01 ---------\n");
    printf("Silver result is %d\n", silver());
    printf("Gold result is %d\n", gold());
    printf("--------------------------\n");
    return 0;
}