#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBD4_BUILD_TESTS)
  include(CTest)

  set(
    tests
    any
    arc
    array
    bool
    byte
    char
    crypto
    enum
    error
    fn
    globals
    map
    number
    object
    optional
    rand
    reference
    rune
    safe
    ssl
    string
    union
  )

  foreach (test ${tests})
    add_executable(${PROJECT_NAME}-test-${test} test/${test}-test.c test/utils.c)
    target_compile_options(${PROJECT_NAME}-test-${test} PRIVATE -g)
    target_link_libraries(${PROJECT_NAME}-test-${test} PUBLIC d4)
    add_test(${test} ${PROJECT_NAME}-test-${test})

    if (LIBD4_SANITIZER)
      target_link_options(${PROJECT_NAME}-test-${test} PRIVATE "-fsanitize=address")
    endif ()
  endforeach ()

  if (LIBD4_SANITIZER)
    set(
      LIBD4_ASAN_OPTIONS

      "abort_on_error=0"
      "exitcode=255"
      "detect_invalid_pointer_pairs=2"
      "detect_leaks=1"
      "detect_stack_use_after_return=1"
      "print_suppressions=0"
      "track_origins=1"
    )

    list(JOIN LIBD4_ASAN_OPTIONS ":" LIBD4_ASAN_OPTIONS)

    set_tests_properties(
      ${tests}
      PROPERTIES
      ENVIRONMENT "ASAN_OPTIONS=${LIBD4_ASAN_OPTIONS};LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/lsan.supp"
    )
  endif ()
endif ()
