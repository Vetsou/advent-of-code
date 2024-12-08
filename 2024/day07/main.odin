package main

import "core:os"
import "core:fmt"
import "core:strings"
import "core:strconv"
import "core:math"

INPUT_FILE :: "test_input.txt"

read_input :: proc(filename: string) -> (input_data: string, success: bool) {
  data, ok := os.read_entire_file(filename);
  return string(data), ok;
}

conv_to_int_arr :: proc(str_nums: []string) -> [dynamic]int {
  nums_buff: [dynamic]int;
  for str_num in str_nums {
    append(&nums_buff, strconv.atoi(str_num));
  }
  return nums_buff;
}

generate_opers :: proc(combi_idx: int, length: int) -> [dynamic]u8 {
  opers: [dynamic]u8;
  
  oper_list := []u8{'+', '*', '|'}
  combi_idx_buff := combi_idx;

  for i := 0; i < length; i += 1 {
    oper_idx := combi_idx_buff % 3;
    append(&opers, oper_list[oper_idx]);
    combi_idx_buff /= 3;
  }

  return opers;
}

eval_expr :: proc(nums: [dynamic]int, opers: [dynamic]u8) -> int {
  result := nums[0];

  for i := 0; i < len(opers); i += 1 {
    if opers[i] == '+' {
      result += nums[i + 1];
    } else if opers[i] == '*' {
      result *= nums[i + 1];
    } else if opers[i] == '|' {
      buff1, buff2: [20]byte;
      right := strconv.itoa(buff1[:], result);
      left := strconv.itoa(buff2[:], nums[i + 1]);

      result = strconv.atoi(strings.join([]string{right, left}, ""));
    }
  }
  return result;
}

is_eq_valid :: proc(expected: int, nums: [dynamic]int) -> bool {
  combinations := cast(int) math.pow(cast(f64) 3, cast(f64) (len(nums) - 1));

  for i := 0; i < combinations; i += 1 {
    opers := generate_opers(i, len(nums) - 1);
    defer delete(opers);

    if eval_expr(nums, opers) == expected {
      return true;
    }
  }

  return false;
}

main :: proc() {
  input, ok := read_input(INPUT_FILE);
  if !ok {
    fmt.println("Error reading file");
    return;
  }
  defer delete(input);

  it := string(input);
  total_cali := 0;

  for line in strings.split_lines_iterator(&it) {
    equation_parts := strings.split(line, ": ");
    defer delete(equation_parts);

    result := strconv.atoi(equation_parts[0]);
    nums := conv_to_int_arr(strings.split(equation_parts[1], " "));

    if is_eq_valid(result, nums) { total_cali += result; }
    delete(nums);
  }

  fmt.println("Result:", total_cali);
}