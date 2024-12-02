package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"
import "core:math"
import "core:sort"

NUM_COUNT :: 1000
INPUT_FILE :: "test_input.txt"

part_1_code :: proc() {
  data, ok := os.read_entire_file(INPUT_FILE);
  if !ok {
    fmt.printfln("Error reading file");
    return;
  }
  defer delete(data);

  it := string(data);
  i := 0;
  list_1: [NUM_COUNT]int;
  list_2: [NUM_COUNT]int;

  for line in strings.split_lines_iterator(&it) {
    parts := strings.split(line, "   ");

    if len(parts) == 2 {
      list_1[i] = strconv.atoi(parts[0]);
      list_2[i] = strconv.atoi(parts[1]);
    } else {
        fmt.println("Malformed line", line);
        return;
    }
    i += 1;
  }

  sort.quick_sort(list_1[:]);
  sort.quick_sort(list_2[:]);

  sum := 0;
  for i = 0; i < NUM_COUNT; i += 1 {
    sum += math.abs(list_1[i] - list_2[i])
  }

  fmt.printf("Result is %d", sum);
}

part_2_code :: proc() {
  data, ok := os.read_entire_file(INPUT_FILE);
  if !ok {
    fmt.printfln("Error reading file");
    return;
  }
  defer delete(data);

  it := string(data);
  i := 0;
  list_1: [NUM_COUNT]int;
  sim_map: map[int]int;

  for line in strings.split_lines_iterator(&it) {
    parts := strings.split(line, "   ");

    if len(parts) == 2 {
      list_1[i] = strconv.atoi(parts[0]);
      value2 := strconv.atoi(parts[1]);

      if _, ok := sim_map[value2]; ok {
        sim_map[value2] += 1;
      } else {
        sim_map[value2] = 1;
      }
    } else {
        fmt.println("Malformed line", line);
        return;
    }
    i += 1;
  }

  sum := 0;
  for i = 0; i < NUM_COUNT; i += 1 {
    if val, ok := sim_map[list_1[i]]; ok {
      sum += list_1[i] * val;
    }
  }

  fmt.printf("Result is %d", sum);
}

main :: proc() {
  part_2_code();
}