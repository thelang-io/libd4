/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "map.h"

const double D4_MAP_LOAD_FACTOR = 0.75;

size_t d4_map_calc_cap (size_t cap, size_t len) {
  while (d4_map_should_reserve(cap, len)) {
    cap *= 2;
  }

  return cap;
}

size_t d4_map_hash (d4_str_t id, size_t cap) {
  size_t result = 0xCBF29CE484222325;

  for (size_t i = 0; i < id.len; i++) {
    result = (size_t) ((size_t) (result * (size_t) 0x00000100000001B3) ^ (size_t) id.data[i]);
  }

  return result % cap;
}

bool d4_map_should_reserve (size_t cap, size_t len) {
  return len >= (size_t) ((double) cap * D4_MAP_LOAD_FACTOR);
}
