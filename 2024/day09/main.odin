package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"

INPUT_FILE :: "test_input.txt"

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

task1 :: proc() {
  input := read_input(INPUT_FILE) or_else panic("Error reading file");
  defer delete(input);

  buff := make([dynamic]rune);
  defer delete(buff);

  curr_num := rune('0');
  is_empty_stage := false;

  for num_rune in input {
    num := int(num_rune - '0');
    if is_empty_stage {
      for j := 0; j < num; j += 1 do append(&buff, '.');
      is_empty_stage = !is_empty_stage;
    } else {
      for j := 0; j < num; j += 1 do append(&buff, curr_num);
      curr_num += 1;
      if curr_num == 10 do curr_num = 0;
      is_empty_stage = !is_empty_stage;
    }
  }

  j := len(buff) - 1;
  for i := 0; i < j; i += 1 {
    if buff[i] == '.' {
      for i < j {
        if buff[j] != '.' {
          buff[j], buff[i] = '.', buff[j];
          j -= 1;
          break;
        }
        j -= 1;
      }
    }
  }

  checksum := 0;
  for i := 0; i < len(buff); i += 1 {
    if buff[i] == '.' do break;
    checksum += i * (int(buff[i] - '0'));
  }

  fmt.println(checksum);
}

main :: proc() {
  task1()
}