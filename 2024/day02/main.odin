package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"
import "core:math"

NUM_COUNT :: 1000
INPUT_FILE :: "test_input.txt"

is_safe :: proc(levels: []int) -> bool {
  asc := true;
  desc := true;

  for i := 0; i < len(levels) - 1; i += 1 {
    diff := math.abs(levels[i] - levels[i + 1]);

    if diff < 1 || diff > 3 { return false; }
    if levels[i] < levels[i + 1] { desc = false; }
    if levels[i] > levels[i + 1] { asc = false; }
  }

  return asc || desc;
}

is_dampener_safe :: proc(levels: []int) -> bool {
  for i := 0; i < len(levels); i += 1 {
    temp := make([]int, len(levels) - 1);
    defer delete(temp);

    index := 0;

    for j := 0; j < len(levels); j += 1 {
      if j == i { continue; }

      temp[index] = levels[j];
      index += 1;
    }

    if is_safe(temp) { return true; }
  }

  return false;
}

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

main :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }

  safe_reports := 0;

  for report in strings.split_lines_iterator(&input) {
    levels := strings.split(report, " ");
    
    nums := make([]int, len(levels));
    defer delete(nums);

    for level, i in levels {
      nums[i] = strconv.atoi(level);
    }

    if is_dampener_safe(nums) { safe_reports += 1; }
  }

  fmt.println("Number of safe reports:", safe_reports);
}