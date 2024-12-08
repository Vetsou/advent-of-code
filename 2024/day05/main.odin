package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"
import "core:sort"

INPUT_FILE :: "test_input.txt"

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

check_val :: proc(num: int, rule_arr: [dynamic]int) -> bool {
  for rule in rule_arr {
    if rule == num { return true; }
  }
  return false;
}

task1 :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }
  defer delete(input);

  rules: map[string][dynamic]int;
  defer delete(rules);

  it := string(input);
  for line in strings.split_lines_iterator(&it) {
    if line == "" { break; }
    pair := strings.split(line, "|");

    key := pair[1];
    val := strconv.atoi(pair[0]);

    if arr, ok := rules[key]; ok {
      append(&rules[key], val);
    } else {
      rules[key] = make([dynamic]int);
      append(&rules[key], val);
    }
  }
  
  sum := 0;
  for line in strings.split_lines_iterator(&it) {
    codes := strings.split(line, ",");
    is_correct := true;

    for i := 1; i < len(codes); i += 1 {
      for j := i - 1; j >= 0; j -= 1 {
        is_correct = check_val(strconv.atoi(codes[j]), rules[codes[i]]);
        if !is_correct { break; }
      }
      if !is_correct { break; }
    }
    if is_correct {
      middle_idx: int = len(codes) / 2;
      sum += strconv.atoi(codes[middle_idx]);
    }
  }

  fmt.printfln("Result is: %d", sum);
  for _, vals in rules { delete(vals); }
}

conv_codes :: proc(line: string) -> [dynamic]int {
  codes_str := strings.split(line, ",");
  codes: [dynamic]int;

  for code_str in codes_str {
    append(&codes, strconv.atoi(code_str));
  }
  return codes;
}

main :: proc() {
  task1();
}