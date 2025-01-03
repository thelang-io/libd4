/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/number.h>
#include <d4/object.h>

D4_OBJECT_FORWARD_DECLARE(Animal)

D4_OBJECT_DECLARE(Animal, {
  d4_str_t name;
  int32_t age;
}, const d4_str_t name, const int32_t age)

D4_OBJECT_DEFINE(Animal, Animal, {
  self.name = d4_str_copy(name);
  self.age = age;
}, {
  result.name = d4_str_copy(self.name);
  result.age = self.age;
}, {
  return d4_str_eq(self.name, rhs.name) && self.age == rhs.age;
}, {
  d4_str_free(self.name);
}, {
  result = d4_obj_str_append(result, d4_str_alloc(L"name"), d4_str_quoted_escape(self.name));
  result = d4_obj_str_append(result, d4_str_alloc(L"age"), d4_i32_str(self.age));
}, const d4_str_t name, const int32_t age)

int main(void) {
  d4_str_t dog_name = d4_str_alloc(L"Barkley");
  d4_str_t cat_name = d4_str_alloc(L"Katy");
  d4_obj_Animal_t dog = d4_obj_Animal_alloc(dog_name, 10);
  d4_obj_Animal_t cat = d4_obj_Animal_alloc(cat_name, 4);
  d4_obj_Animal_t dog_copy = d4_obj_Animal_copy(dog);

  d4_str_t cat_str = d4_obj_Animal_str(dog);
  d4_str_t dog_str = d4_obj_Animal_str(dog);

  wprintf(L"dog == cat: %ls\n", d4_obj_Animal_eq(dog, cat) ? L"equal" : L"not equal");
  wprintf(L"dog == dog copy: %ls\n", d4_obj_Animal_eq(dog, dog_copy) ? L"equal" : L"not equal");
  wprintf(L"dog: %ls\n", dog_str.data);
  wprintf(L"cat: %ls\n", cat_str.data);

  cat = d4_obj_Animal_realloc(cat, dog);
  wprintf(L"dog == cat: %ls\n", d4_obj_Animal_eq(dog, cat) ? L"equal" : L"not equal");

  d4_str_free(cat_str);
  d4_str_free(dog_str);

  d4_obj_Animal_free(dog_copy);
  d4_obj_Animal_free(dog);
  d4_obj_Animal_free(cat);
  d4_str_free(dog_name);

  return 0;
}
