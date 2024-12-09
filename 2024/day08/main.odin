package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"
import "core:math"

INPUT_FILE :: "test_input.txt"

WIDTH  :: 12
HEIGHT :: 12

Position :: struct { y: int, x: int }

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

idx_in_bounds :: proc(x: int, y: int) -> bool {
  return x < WIDTH && x >= 0 && y < HEIGHT && y >= 0;
}

task1 :: proc() {
  input := read_input(INPUT_FILE) or_else panic("Error reading file");
  defer delete(input);

  antenna_map: map[u8][dynamic]Position;
  defer delete(antenna_map);

  it := string(input); y := 0;
  for line in strings.split_lines_iterator(&it) {
    for x := 0; x < WIDTH; x += 1 {
      tile := line[x];

      if tile != '.' {
        if _, ok := antenna_map[tile]; ok {
          append(&antenna_map[tile], Position{ y, x });
        } else {
          antenna_map[tile] = make([dynamic]Position);
          append(&antenna_map[tile], Position{ y, x });
        }
      }
    }
    y += 1;
  }

  antinodes := 0;
  antinode_map: map[Position]bool;
  
  for _, antenna in antenna_map {
    if len(antenna) < 2 do continue;

    for i := 0; i < len(antenna); i += 1 {
      for j := i + 1; j < len(antenna); j += 1 {
        x1 := 2 * antenna[i].x - antenna[j].x;
        y1 := 2 * antenna[i].y - antenna[j].y;

        x2 := 2 * antenna[j].x - antenna[i].x;
        y2 := 2 * antenna[j].y - antenna[i].y;

        if idx_in_bounds(x1, y1) {
          if !antinode_map[Position{ y1, x1 }] do antinodes += 1;
          antinode_map[Position{ y1, x1 }] = true;
        }

        if idx_in_bounds(x2, y2) {
          if !antinode_map[Position{ y2, x2 }] do antinodes += 1;
          antinode_map[Position{ y2, x2 }] = true;
        }
      }
    }
  }

  fmt.println("Result: ", antinodes);
}

task2 :: proc() {
  input := read_input(INPUT_FILE) or_else panic("Error reading file");
  defer delete(input);

  antenna_map: map[u8][dynamic]Position;
  defer delete(antenna_map);

  it := string(input); y := 0;
  for line in strings.split_lines_iterator(&it) {
    for x := 0; x < WIDTH; x += 1 {
      tile := line[x];

      if tile != '.' {
        if _, ok := antenna_map[tile]; ok {
          append(&antenna_map[tile], Position{ y, x });
        } else {
          antenna_map[tile] = make([dynamic]Position);
          append(&antenna_map[tile], Position{ y, x });
        }
      }
    }
    y += 1;
  }

  antinodes := 0;
  antinode_map: map[Position]bool;
  
  for _, antenna in antenna_map {
    if len(antenna) < 2 do continue;

    for i := 0; i < len(antenna); i += 1 {
      for j := i + 1; j < len(antenna); j += 1 {
        x1 := antenna[i].x - antenna[j].x;
        y1 := antenna[i].y - antenna[j].y;

        x2 := antenna[j].x - antenna[i].x;
        y2 := antenna[j].y - antenna[i].y;

        buffx := antenna[i].x; buffy := antenna[i].y;
        for idx_in_bounds(buffx, buffy) {
          if !antinode_map[Position{ buffy, buffx }] do antinodes += 1;
          antinode_map[Position{ buffy, buffx }] = true;
          buffx += x1; buffy += y1;
        }

        buffx = antenna[j].x; buffy = antenna[j].y;
        for idx_in_bounds(buffx, buffy) {
          if !antinode_map[Position{ buffy, buffx }] do antinodes += 1;
          antinode_map[Position{ buffy, buffx }] = true;
          buffx += x2; buffy += y2;
        }
      }
    }
  }

  fmt.println("Result: ", antinodes);
}

main :: proc() {
  task2()
}