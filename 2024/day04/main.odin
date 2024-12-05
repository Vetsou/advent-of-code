package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"

INPUT_FILE :: "test_input.txt"

XMAS_LEN :: 4

WIDTH :: 10
HEIGHT :: 10

DIR := [8][2]int{
  { 0,  1},
  { 0, -1},
  { 1,  0}, 
  {-1,  0},
  { 1,  1}, 
  { 1, -1},
  {-1,  1},
  {-1, -1}
};

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

check_xmas :: proc(x: int, y: int, x_dir: int, y_dir: int, data: ^[HEIGHT][WIDTH]u8) -> int {
  found_num := 0;
  xmas_word := "XMAS";

  for i := 0; i < XMAS_LEN; i += 1 {
    new_x_dir := x + i * x_dir;
    new_y_dir := y + i * y_dir;
    if new_x_dir >= WIDTH || new_x_dir < 0 || new_y_dir >= HEIGHT || new_y_dir < 0 {
      return 0;
    }

    if data[new_y_dir][new_x_dir] != xmas_word[i] {
      return 0;
    }
  }

  return 1;
}

task1 :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }
  defer delete(input);

  data: [HEIGHT][WIDTH]u8;

  it := string(input);
  y := 0;
  for line in strings.split_lines_iterator(&it) {
    for x := 0; x < WIDTH; x += 1 {
      data[y][x] = line[x];
    }
    y += 1;
  }

  sum := 0;
  for y := 0; y < HEIGHT; y += 1 {
    for x := 0; x < WIDTH; x += 1 {

      if data[y][x] == 'X' {
        for d := 0; d < 8; d += 1 {
          sum += check_xmas(x, y, DIR[d][0], DIR[d][1], &data);
        }
      }

    }
  }

  fmt.printf("Found 'XMAS': %d", sum);
}

CROSS_DIR := [4][2]int{
  { 1,  1},
  {-1, -1}, 
  { 1, -1},
  {-1,  1},
};

check_bounds :: proc(x: int, y: int) -> bool {
  return x >= WIDTH || x < 0 || y >= HEIGHT || y < 0;
}

check_mas :: proc(x: int, y: int, data: ^[HEIGHT][WIDTH]u8) -> int {
  for i := 0; i < 4; i += 2 {
    x_dir1 := x + CROSS_DIR[i][0];
    y_dir1 := y + CROSS_DIR[i][1];

    x_dir2 := x + CROSS_DIR[i+1][0];
    y_dir2 := y + CROSS_DIR[i+1][1];

    if check_bounds(x_dir1, y_dir1) {
      return 0;
    }

    if check_bounds(x_dir2, y_dir2) {
      return 0;
    }

    lett1 := rune(data[y_dir1][x_dir1]);
    lett2 := rune(data[y_dir2][x_dir2]);

    if (lett1 == 'S' && lett2 == 'M') || (lett2 == 'S' && lett1 == 'M') {
      continue;
    }

    return 0;
  }
  return 1;
}

task2 :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }
  defer delete(input);

  data: [HEIGHT][WIDTH]u8;

  it := string(input);
  y := 0;
  for line in strings.split_lines_iterator(&it) {
    for x := 0; x < WIDTH; x += 1 {
      data[y][x] = line[x];
    }
    y += 1;
  }

  sum := 0;
  for y := 0; y < HEIGHT; y += 1 {
    for x := 0; x < WIDTH; x += 1 {

      if data[y][x] == 'A' {
        sum += check_mas(x, y, &data);
      }

    }
  }

  fmt.printf("Found 'XMAS': %d", sum);
}

main :: proc() {
  task2();
}