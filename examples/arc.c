/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/arc.h"
#include "../include/d4/number.h"
#include "../include/d4/object.h"

D4_OBJECT_FORWARD_DECLARE(Person)
D4_ARC_FORWARD_DECLARE(obj_Person)

D4_OBJECT_DECLARE(Person, {
  int32_t age;
}, const int32_t age)

D4_ARC_DECLARE(obj_Person, d4_obj_Person_t)

D4_OBJECT_DEFINE(Person, Person, {
  self.age = age;
}, {
  result.age = self.age;
}, {
  return self.age == rhs.age;
}, {
  (void) self;
}, {
  result = d4_obj_str_append(result, d4_str_alloc(L"age"), d4_i32_str(self.age));
}, const int32_t age)

D4_ARC_DEFINE(obj_Person, d4_obj_Person_t, d4_obj_Person_copy(ref), d4_obj_Person_eq(lhs_ref, rhs_ref), d4_obj_Person_free(ref), d4_obj_Person_str(ref))

int main (void) {
  d4_obj_Person_t __1;
  d4_obj_Person_t __2;
  d4_arc_obj_Person_t person_0 = d4_arc_obj_Person_alloc(__1 = d4_obj_Person_alloc(10));
  d4_arc_obj_Person_t person_1 = d4_arc_obj_Person_alloc(__2 = d4_obj_Person_alloc(20));
  d4_arc_obj_Person_t person_2 = d4_arc_obj_Person_copy(person_1);

  d4_str_t p1_str = d4_arc_obj_Person_str(person_0);
  d4_str_t p2_str = d4_arc_obj_Person_str(person_1);

  person_2 = d4_arc_obj_Person_realloc(person_2, person_0->ref);

  wprintf(L"person_0: %ls\n", p1_str.data);
  wprintf(L"person_1: %ls\n", p2_str.data);

  wprintf(L"person_0 eq person_1: %ls\n", d4_arc_obj_Person_eq(person_0, person_1) ? L"true" : L"false");
  wprintf(L"person_0 eq person_2: %ls\n", d4_arc_obj_Person_eq(person_0, person_2) ? L"true" : L"false");

  d4_str_free(p2_str);
  d4_str_free(p1_str);
  d4_arc_obj_Person_free(person_2);
  d4_arc_obj_Person_free(person_1);
  d4_arc_obj_Person_free(person_0);
  d4_obj_Person_free(__2);
  d4_obj_Person_free(__1);
}
