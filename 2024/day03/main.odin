package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"

NUM_COUNT :: 1000
INPUT_FILE :: "test_input.txt"

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

consume_do :: proc(ptr: ^int, input: string) -> (new_state: bool, found: bool) {
  if ptr^ + 4 > len(input) { return false, false; }
  is_enabled := input[ptr^:ptr^+4] == "do()";

  if is_enabled { return true, true; }

  if ptr^ + 7 > len(input) { return false, false; }
  is_disabled := input[ptr^:ptr^+7] == "don't()";

  if is_disabled { return false, true; }
  return false, false;
}

consume_mul :: proc(ptr: ^int, input: string) -> bool {
  if ptr^ + 4 > len(input) { return false; }
  is_mul := input[ptr^:ptr^+4] == "mul(";

  if !is_mul { return false; }

  ptr^ += 4;
  return true;
}

is_num :: proc(char: u8) -> bool {
  return char >= '0' && char <= '9';
}

consume_nums :: proc(ptr: ^int, input: string) -> (int, bool) {
  num_start := ptr^;
  for is_num(input[ptr^]) && ptr^ < len(input) {
    ptr^ += 1;
  }

  if ptr^ == len(input) { return 0, false; }
  val1 := strconv.atoi(input[num_start:ptr^]);

  if input[ptr^] != ',' {
    return 0, false;
  }

  ptr^ += 1;
  num_start = ptr^;
  for is_num(input[ptr^]) && ptr^ < len(input) {
    ptr^ += 1; 
  }

  if ptr^ == len(input) { return 0, false; }
  val2 := strconv.atoi(input[num_start:ptr^]);

  if input[ptr^] != ')' { return 0, false; }

  return val1 * val2, true;
}

find_mul :: proc(input: string) -> int {
  sum := 0;
  do_enable := true;

  for i := 0; i < len(input); i += 1 {
    if input[i] == 'd' {
      new_state, found := consume_do(&i, input);
      if found { do_enable = new_state; }
    }

    if input[i] == 'm' && do_enable {
      found := consume_mul(&i, input);
      if !found { continue; }

      result, ok := consume_nums(&i, input);
      if ok { sum += result; }
    }
  }
  return sum;
}

main :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }

  fmt.printf("Answer is: %d", find_mul(input));
}