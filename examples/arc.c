/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

// TODO: Implement same type of imports for all examples
#include "../include/d4/arc.h"
#include "../include/d4/number.h"
#include "../include/d4/object.h"

D4_OBJECT_FORWARD_DECLARE(Animal)
D4_OBJECT_FORWARD_DECLARE(Person)
D4_ARC_FORWARD_DECLARE(Person)

D4_OBJECT_DECLARE(Animal, {
  d4_arc_Person_t owner;
}, const d4_arc_Person_t owner)

D4_OBJECT_DECLARE(Person, {
  int32_t age;
}, const int32_t age)

D4_ARC_DECLARE(Person, d4_obj_Person_t)

D4_OBJECT_DEFINE(Animal, Animal, {
  self.owner = d4_arc_Person_copy(owner);
}, {
  result.owner = d4_arc_Person_copy(self.owner);
}, {
  return d4_arc_Person_eq(self.owner, rhs.owner);
}, {
  d4_arc_Person_free(self.owner);
}, {
  result = d4_obj_str_append(result, d4_str_alloc(L"owner"), d4_arc_Person_str(self.owner));
}, const d4_arc_Person_t owner)

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

D4_ARC_DEFINE(Person, d4_obj_Person_t, d4_obj_Person_copy(ref), d4_obj_Person_copy(ref), d4_obj_Person_eq(*self->ref, *rhs->ref), d4_obj_Person_free(*self->ref), d4_obj_Person_str(*self->ref))

int main (void) {
  d4_obj_Person_t __THE_1;
  d4_arc_Person_t person_0 = d4_arc_Person_alloc(__THE_1 = d4_obj_Person_alloc(10));
  d4_obj_Animal_t dog_0 = d4_obj_Animal_alloc(person_0);

  // TODO: Add more examples

  d4_arc_Person_free(person_0);
  d4_obj_Animal_free(dog_0);
  d4_obj_Person_free(__THE_1);
}
