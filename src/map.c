/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "map.h"

const double THE_MAP_LOAD_FACTOR = 0.75;

size_t the_map_calc_cap (size_t cap, size_t len) {
  while (the_map_should_calc_cap(cap, len)) {
    cap *= 2;
  }

  return cap;
}

size_t the_map_hash (the_str_t id, size_t cap) {
  size_t result = 0xCBF29CE484222325;

  for (size_t i = 0; i < id.len; i++) {
    result = (size_t) ((size_t) (result * (size_t) 0x00000100000001B3) ^ (size_t) id.data[i]);
  }

  return result % cap;
}

bool the_map_should_calc_cap (size_t cap, size_t len) {
  return len >= (size_t) ((double) cap * THE_MAP_LOAD_FACTOR);
}
