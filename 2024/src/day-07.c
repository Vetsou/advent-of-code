#include <string.h>
#include <math.h>

#define AOC_IMPLEMENTATION
#include "aoc.h"

#define INPUT_FILE "src/input/input07.txt"
#define MAX_TOKENS 64


uint64_t eval_expr(uint64_t* nums, int nums_len, unsigned char* opers) {
    uint64_t result = nums[0];
    for (int i = 0; i < nums_len - 1; i++) {
        if (opers[i] == '+') result += nums[i + 1];
        else if (opers[i] == '*') result *= nums[i + 1];
        else {
            char combined[100];
            snprintf(combined, sizeof(combined), "%llu%llu", result, nums[i + 1]);
            result = atoll(combined);
        }
    }
    return result;
}

unsigned char* generate_opers_silver(int combi_idx, int length) {
    unsigned char* opers = malloc(sizeof(*opers) * length);
    const char oper_list[] = {'+', '*'};
    for (int i = 0; i < length; i++, combi_idx /= 2) opers[i] = oper_list[combi_idx % 2];
    return opers;
}

bool silver(uint64_t expected, uint64_t* nums, int nums_len) {
    int combinations = pow(2, nums_len - 1);
    for (int i = 0; i < combinations; i++) {
        unsigned char* opers = generate_opers_silver(i, nums_len - 1);
        if (eval_expr(nums, nums_len, opers) == expected) {
            free(opers);
            return true;
        }
        free(opers);
    }
    return false;
}

unsigned char* generate_opers_gold(int combi_idx, int length) {
    unsigned char* opers = malloc(sizeof(*opers) * length);
    const char oper_list[] = {'+', '*', '|'};
    for (int i = 0; i < length; i++, combi_idx /= 3) opers[i] = oper_list[combi_idx % 3];
    return opers;
}

bool gold(uint64_t expected, uint64_t* nums, int nums_len) {
    int combinations = pow(3, nums_len - 1);
    for (int i = 0; i < combinations; i++) {
        unsigned char* opers = generate_opers_gold(i, nums_len - 1);
        if (eval_expr(nums, nums_len, opers) == expected) {
            free(opers);
            return true;
        }
        free(opers);
    }
    return false;
}

int main() {
    FILE *file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("Error reading file\n");
        return -1;
    }

    char line[128];

    uint64_t silver_result = 0;
    uint64_t gold_result = 0;

    while (fgets(line, sizeof(line), file)) {
        int split_count;
        char **split_result = split_string(line, ": \n", &split_count, MAX_TOKENS);
        uint64_t *nums = str_array_to_int64_array(split_result, split_count);

        if (silver(nums[0], nums + 1, split_count - 1)) silver_result += nums[0];
        if (gold(nums[0], nums + 1, split_count - 1)) gold_result += nums[0];

        free_split_str(split_result, split_count);
        free(nums);
    }

    printf("--------- DAY 07 ---------\n");
    printf("Silver result is %llu\n", silver_result);
    printf("Gold result is %llu\n", gold_result);
    printf("--------------------------\n");

    fclose(file);
    return 0;
}