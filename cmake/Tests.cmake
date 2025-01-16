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

      "abort_on_error=1"
      "alloc_dealloc_mismatch=1"
      "detect_container_overflow=1"
      "detect_invalid_pointer_pairs=2"
      "detect_leaks=1"
      "detect_odr_violation=2"
      "detect_stack_use_after_return=1"
      "check_initialization_order=1"
      "fast_unwind_on_malloc=1"
      "halt_on_error=1"
      "intercept_tls_get_addr=1"
      "leak_check_at_exit=1"
      "strict_init_order=1"
      "strict_memcmp=1"
      "strict_string_checks=1"
      "symbolize=1"
      "track_origins=1"
    )

    list(JOIN LIBD4_ASAN_OPTIONS ":" LIBD4_ASAN_OPTIONS)

    set_tests_properties(
      ${tests}
      PROPERTIES
      ENVIRONMENT "ASAN_OPTIONS=${LIBD4_ASAN_OPTIONS}"
    )
  endif ()
endif ()
