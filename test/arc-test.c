/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

// TODO: Implement same type of imports for all tests
#include <assert.h>
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

static void test_arc_alloc (void) {
  d4_obj_Person_t person = d4_obj_Person_alloc(25);
  d4_arc_obj_Person_t arc = d4_arc_obj_Person_alloc(person);

  assert(((void) "ARC allocation should not return NULL", arc != NULL));
  assert(((void) "Initial reference count should be 1", arc->count == 1));
  assert(((void) "ARC reference should store copy of object", arc->ref.age == 25));

  d4_arc_obj_Person_free(arc);
  d4_obj_Person_free(person);
}

static void test_arc_copy (void) {
  d4_obj_Person_t person = d4_obj_Person_alloc(30);
  d4_arc_obj_Person_t arc1 = d4_arc_obj_Person_alloc(person);
  d4_arc_obj_Person_t arc2 = d4_arc_obj_Person_copy(arc1);

  assert(((void) "Copied ARC should be same instance", arc1 == arc2));
  assert(((void) "Reference count should be 2 after copy", arc1->count == 2));

  d4_arc_obj_Person_free(arc2);
  d4_arc_obj_Person_free(arc1);
  d4_obj_Person_free(person);
}

static void test_arc_eq (void) {
  d4_obj_Person_t person1 = d4_obj_Person_alloc(35);
  d4_obj_Person_t person2 = d4_obj_Person_alloc(35);
  d4_obj_Person_t person3 = d4_obj_Person_alloc(40);

  d4_arc_obj_Person_t arc1 = d4_arc_obj_Person_alloc(person1);
  d4_arc_obj_Person_t arc2 = d4_arc_obj_Person_alloc(person2);
  d4_arc_obj_Person_t arc3 = d4_arc_obj_Person_alloc(person3);

  assert(((void) "ARCs with same objects should be equal", d4_arc_obj_Person_eq(arc1, arc2)));
  assert(((void) "ARCs with different objects should not be equal", !d4_arc_obj_Person_eq(arc1, arc3)));

  d4_arc_obj_Person_free(arc1);
  d4_arc_obj_Person_free(arc2);
  d4_arc_obj_Person_free(arc3);

  d4_obj_Person_free(person1);
  d4_obj_Person_free(person2);
  d4_obj_Person_free(person3);
}

static void test_arc_free (void) {
  d4_obj_Person_t person = d4_obj_Person_alloc(45);
  d4_arc_obj_Person_t arc = d4_arc_obj_Person_alloc(person);
  d4_arc_obj_Person_t copy = d4_arc_obj_Person_copy(arc);

  assert(((void) "Reference count should be 2 after copy", arc->count == 2));
  d4_arc_obj_Person_free(arc);
  assert(((void) "Reference count should be 1 after freeing copy", copy->count == 1));

  d4_arc_obj_Person_free(copy);
  d4_obj_Person_free(person);
}

static void test_arc_get (void) {
  d4_obj_Person_t person = d4_obj_Person_alloc(50);
  d4_arc_obj_Person_t arc = d4_arc_obj_Person_alloc(person);
  d4_obj_Person_t ref = d4_arc_obj_Person_get(arc);

  assert(((void) "Retrieved reference should be the same as input", d4_obj_Person_eq(person, ref)));

  d4_arc_obj_Person_free(arc);
  d4_obj_Person_free(person);
}

static void test_arc_realloc (void) {
  d4_obj_Person_t person1 = d4_obj_Person_alloc(55);
  d4_obj_Person_t person2 = d4_obj_Person_alloc(60);

  d4_arc_obj_Person_t arc1 = d4_arc_obj_Person_alloc(person1);
  d4_arc_obj_Person_t arc2 = d4_arc_obj_Person_alloc(person2);

  arc1 = d4_arc_obj_Person_realloc(arc1, arc2);
  assert(((void) "Reallocated ARC should be the same as second object", d4_arc_obj_Person_eq(arc1, arc2)));

  d4_arc_obj_Person_free(arc1);
  d4_arc_obj_Person_free(arc2);

  d4_obj_Person_free(person1);
  d4_obj_Person_free(person2);
}

static void test_arc_str (void) {
  d4_obj_Person_t person = d4_obj_Person_alloc(65);
  d4_arc_obj_Person_t arc = d4_arc_obj_Person_alloc(person);

  d4_str_t s1 = d4_str_alloc(L"Person{age: 65}");
  d4_str_t s1_cmp = d4_arc_obj_Person_str(arc);

  assert(((void) "String representation should not be NULL", s1_cmp.data != NULL));
  assert(((void) "String representation should equal object string representation", d4_str_eq(s1_cmp, s1)));

  d4_str_free(s1_cmp);
  d4_str_free(s1);

  d4_arc_obj_Person_free(arc);
  d4_obj_Person_free(person);
}

int main (void) {
  test_arc_alloc();
  test_arc_copy();
  test_arc_eq();
  test_arc_free();
  test_arc_get();
  test_arc_realloc();
  test_arc_str();
}
