/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/number.h>
#include <d4/object.h>
#include <assert.h>

D4_OBJECT_DECLARE(TestEmpty, {
  void *_;
}, void *_)

D4_OBJECT_DECLARE(Test0, {
  d4_str_t prop;
}, const d4_str_t prop)

D4_OBJECT_DECLARE(Test, {
  d4_str_t prop1;
  int32_t prop2;
}, const d4_str_t prop1, const int32_t prop2)

D4_OBJECT_DEFINE(TestEmpty, TestEmpty, {
  self._ = _;
}, {
  result._ = self._;
}, {
  return self._ == rhs._;
}, {
  (void) self;
}, {
  (void) self;
}, void *_)

D4_OBJECT_DEFINE(Test0, Test0, {
  self.prop = d4_str_copy(prop);
}, {
  result.prop = d4_str_copy(self.prop);
}, {
  return d4_str_eq(self.prop, rhs.prop);
}, {
  d4_str_free(self.prop);
}, {
  result = d4_obj_str_append(result, d4_str_alloc(L"prop"), d4_str_quoted_escape(self.prop));
}, const d4_str_t prop)

D4_OBJECT_DEFINE(Test, Test, {
  self.prop1 = d4_str_copy(prop1);
  self.prop2 = prop2;
}, {
  result.prop1 = d4_str_copy(self.prop1);
  result.prop2 = self.prop2;
}, {
  return d4_str_eq(self.prop1, rhs.prop1) && self.prop2 == rhs.prop2;
}, {
  d4_str_free(self.prop1);
}, {
  result = d4_obj_str_append(result, d4_str_alloc(L"prop1"), d4_str_quoted_escape(self.prop1));
  result = d4_obj_str_append(result, d4_str_alloc(L"prop2"), d4_i32_str(self.prop2));
}, const d4_str_t prop1, const int32_t prop2)

static void test_object_alloc (void) {
  d4_str_t p = d4_str_alloc(L"string");
  d4_obj_Test_t o = d4_obj_Test_alloc(p, 10);

  assert(((void) "Object type prop1 is set", d4_str_eq(o.prop1, p)));
  assert(((void) "Object type prop2 is set", o.prop2 == 10));

  d4_obj_Test_free(o);
  d4_str_free(p);
}

static void test_object_copy (void) {
  d4_str_t p = d4_str_alloc(L"string");
  d4_obj_Test_t o1 = d4_obj_Test_alloc(p, 10);
  d4_obj_Test_t o2 = d4_obj_Test_copy(o1);

  assert(((void) "Copies object type", d4_obj_Test_eq(o1, o2)));

  d4_obj_Test_free(o1);
  d4_obj_Test_free(o2);
  d4_str_free(p);
}

static void test_object_eq (void) {
  d4_str_t p1 = d4_str_alloc(L"string1");
  d4_str_t p2 = d4_str_alloc(L"string2");
  d4_obj_Test_t o1 = d4_obj_Test_alloc(p1, 10);
  d4_obj_Test_t o2 = d4_obj_Test_alloc(p1, 10);
  d4_obj_Test_t o3 = d4_obj_Test_alloc(p1, 20);
  d4_obj_Test_t o4 = d4_obj_Test_alloc(p2, 10);
  d4_obj_TestEmpty_t o5 = d4_obj_TestEmpty_alloc(NULL);
  d4_obj_TestEmpty_t o6 = d4_obj_TestEmpty_alloc(NULL);

  assert(((void) "Object type equal itself", d4_obj_Test_eq(o1, o1)));
  assert(((void) "Object type equal similar object type", d4_obj_Test_eq(o1, o2)));
  assert(((void) "Object type does not equal when different int value", !d4_obj_Test_eq(o1, o3)));
  assert(((void) "Object type does not equal when different str value", !d4_obj_Test_eq(o1, o4)));
  assert(((void) "Empty object types are equal", d4_obj_TestEmpty_eq(o5, o6)));

  d4_str_free(p1);
  d4_str_free(p2);
  d4_obj_Test_free(o1);
  d4_obj_Test_free(o2);
  d4_obj_Test_free(o3);
  d4_obj_Test_free(o4);
  d4_obj_TestEmpty_free(o5);
  d4_obj_TestEmpty_free(o6);
}

static void test_object_free (void) {
  d4_str_t p1 = d4_str_alloc(L"string1");
  d4_str_t p2 = d4_str_alloc(L"string2");
  d4_obj_Test_t o1 = d4_obj_Test_alloc(p1, 10);
  d4_obj_Test_t o2 = d4_obj_Test_alloc(p2, 20);

  d4_obj_Test_free(o1);
  d4_obj_Test_free(o2);
  d4_str_free(p1);
  d4_str_free(p2);
}

static void test_object_realloc (void) {
  d4_str_t p1 = d4_str_alloc(L"string1");
  d4_str_t p2 = d4_str_alloc(L"string2");

  d4_obj_Test_t o1 = d4_obj_Test_alloc(p1, 10);
  d4_obj_Test_t o2 = d4_obj_Test_alloc(p2, 20);

  o2 = d4_obj_Test_realloc(o2, o1);
  assert(((void) "Reallocates object type", d4_obj_Test_eq(o1, o2)));

  d4_obj_Test_free(o1);
  d4_obj_Test_free(o2);
  d4_str_free(p1);
  d4_str_free(p2);
}

static void test_object_str (void) {
  d4_str_t p1 = d4_str_alloc(L"string1");
  d4_str_t p2 = d4_str_alloc(L"string2");

  d4_obj_TestEmpty_t o1 = d4_obj_TestEmpty_alloc(NULL);
  d4_obj_Test0_t o2 = d4_obj_Test0_alloc(p1);
  d4_obj_Test_t o3 = d4_obj_Test_alloc(p2, 20);

  d4_str_t cmp1 = d4_str_alloc(L"TestEmpty{}");
  d4_str_t cmp2 = d4_str_alloc(L"Test0{prop: \"string1\"}");
  d4_str_t cmp3 = d4_str_alloc(L"Test{prop1: \"string2\", prop2: 20}");

  d4_str_t r1 = d4_obj_TestEmpty_str(o1);
  d4_str_t r2 = d4_obj_Test0_str(o2);
  d4_str_t r3 = d4_obj_Test_str(o3);

  assert(((void) "Stringifies empty object type", d4_str_eq(r1, cmp1)));
  assert(((void) "Stringifies single field object type", d4_str_eq(r2, cmp2)));
  assert(((void) "Stringifies two fields object type", d4_str_eq(r3, cmp3)));

  d4_str_free(p1);
  d4_str_free(p2);

  d4_obj_TestEmpty_free(o1);
  d4_obj_Test0_free(o2);
  d4_obj_Test_free(o3);

  d4_str_free(cmp1);
  d4_str_free(cmp2);
  d4_str_free(cmp3);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
}

static void test_object_str_append (void) {
  d4_str_t name1 = d4_str_alloc(L"name1");
  d4_str_t name2 = d4_str_alloc(L"name2");
  d4_str_t name3 = d4_str_alloc(L"name3");

  d4_str_t value1 = d4_str_alloc(L"123");
  d4_str_t value2 = d4_str_alloc(L"\"string\"");
  d4_str_t value3 = d4_str_alloc(L"true");

  d4_str_t r = d4_str_alloc(L"");

  d4_str_t cmp1 = d4_str_alloc(L"name1: 123");
  d4_str_t cmp2 = d4_str_alloc(L"name1: 123, name2: \"string\"");
  d4_str_t cmp3 = d4_str_alloc(L"name1: 123, name2: \"string\", name3: true");

  r = d4_obj_str_append(r, name1, value1);
  assert(((void) "Appends first field to object str", d4_str_eq(r, cmp1)));
  r = d4_obj_str_append(r, name2, value2);
  assert(((void) "Appends second field to object str", d4_str_eq(r, cmp2)));
  r = d4_obj_str_append(r, name3, value3);
  assert(((void) "Appends third field to object str", d4_str_eq(r, cmp3)));

  d4_str_free(r);

  d4_str_free(cmp1);
  d4_str_free(cmp2);
  d4_str_free(cmp3);
}

int main (void) {
  test_object_alloc();
  test_object_copy();
  test_object_eq();
  test_object_free();
  test_object_realloc();
  test_object_str();
  test_object_str_append();
}
