package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"
import "core:sort"

INPUT_FILE :: "test_input.txt"

WIDTH :: 10
HEIGHT :: 10

DIR := [4][2]int{
  {-1,  0},
  { 0,  1},
  { 1,  0}, 
  { 0, -1},
}

Tile :: struct {
  type: u8,
  is_visited: bool
}

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

idx_out_of_bounds :: proc(x: int, y: int) -> bool {
  return x >= WIDTH || x < 0 || y >= HEIGHT || y < 0;
}

rotate :: proc(curr_dir_idx: int) -> int {
  if curr_dir_idx == 3 { return 0; }
  return curr_dir_idx + 1;
}

main :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }
  defer delete(input);

  data: [HEIGHT][WIDTH]Tile;
  dir_idx := 0;
  guard_pos: [2]int;

  it := string(input); y := 0;
  for line in strings.split_lines_iterator(&it) {
    for x := 0; x < WIDTH; x += 1 {
      if line[x] == '^' {
        data[y][x] = Tile { '.', true };
        guard_pos[0] = y; guard_pos[1] = x;
        continue;
      }
      data[y][x] = Tile { line[x], false };
    }
    y += 1;
  }

  visited_count := 1;
  loop_count := 0;

  codes: [dynamic]int;

  for true {
    new_y := guard_pos[0] + DIR[dir_idx][0];
    new_x := guard_pos[1] + DIR[dir_idx][1];
    if idx_out_of_bounds(new_x, new_y) { break; }

    if data[new_y][new_x].type == '#' {
      dir_idx = rotate(dir_idx);
      continue;
    }

    if !data[new_y][new_x].is_visited {
      visited_count += 1;
    }

    data[new_y][new_x].is_visited = true;
    guard_pos[0] = new_y;
    guard_pos[1] = new_x;
  }

  fmt.println("Result:", visited_count, loop_count);
}