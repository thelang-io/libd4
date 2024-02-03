#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.5)
project(libthe VERSION 0.1.0 LANGUAGES C)

include(GNUInstallDirs)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra \
-Wabstract-vbase-init \
-Walloca \
-Wanon-enum-enum-conversion \
-Warc-repeated-use-of-weak \
-Warray-bounds-pointer-arithmetic \
-Wassign-enum \
-Watomic-implicit-seq-cst \
-Watomic-properties \
-Wbad-function-cast \
-Wbinary-literal \
-Wbind-to-temporary-copy \
-Wc99-compat \
-Wc99-extensions \
-Wcalled-once-parameter \
-Wcast-align \
-Wcast-function-type \
-Wcast-qual \
-Wclass-varargs \
-Wcomma \
-Wcompound-token-split \
-Wconditional-uninitialized \
-Wconsumed \
-Wcovered-switch-default \
-Wcstring-format-directive \
-Wctad-maybe-unsupported \
-Wcuda-compat \
-Wdate-time \
-Wdeclaration-after-statement \
-Wdeprecated \
-Wdeprecated-implementations \
-Wdirect-ivar-access \
-Wdisabled-macro-expansion \
-Wdocumentation \
-Wdocumentation-pedantic \
-Wdouble-promotion \
-Wdtor-name \
-Wduplicate-decl-specifier \
-Wduplicate-enum \
-Wduplicate-method-arg \
-Wduplicate-method-match \
-Wdynamic-exception-spec \
-Wexit-time-destructors \
-Wexpansion-to-defined \
-Wexplicit-ownership-type \
-Wextra-semi \
-Wextra-semi-stmt \
-Wfloat-equal \
-Wformat-non-iso \
-Wformat-pedantic \
-Wformat-type-confusion \
-Wformat=2 \
-Wfour-char-constants \
-Wgcc-compat \
-Wglobal-constructors \
-Wgnu \
-Wheader-hygiene \
-Widiomatic-parentheses \
-Wimplicit-fallthrough \
-Wimplicit-retain-self \
-Wincompatible-function-pointer-types \
-Wincomplete-module \
-Winconsistent-missing-destructor-override \
-Winvalid-or-nonexistent-directory \
-Wlocal-type-template-args \
-Wloop-analysis \
-Wmain \
-Wmax-tokens \
-Wmethod-signatures \
-Wmicrosoft \
-Wmissing-noreturn \
-Wmissing-prototypes \
-Wmissing-variable-declarations \
-Wnewline-eof \
-Wnon-gcc \
-Wnon-virtual-dtor \
-Wnonportable-private-system-apinotes-path \
-Wnonportable-system-include-path \
-Wnullable-to-nonnull-conversion \
-Wobjc-interface-ivars \
-Wobjc-messaging-id \
-Wobjc-missing-property-synthesis \
-Wobjc-property-assign-on-object-type \
-Wobjc-signed-char-bool \
-Wold-style-cast \
-Wopenmp \
-Wover-aligned \
-Woverriding-method-mismatch \
-Wpacked \
-Wpedantic \
-Wpedantic-core-features \
-Wpointer-arith \
-Wpoison-system-directories \
-Wpragmas \
-Wpre-openmp-51-compat \
-Wprofile-instr-missing \
-Wquoted-include-in-framework-header \
-Wreceiver-forward-class \
-Wredundant-parens \
-Wreserved-identifier \
-Wreserved-user-defined-literal \
-Wselector \
-Wshadow-all \
-Wshift-sign-overflow \
-Wsigned-enum-bitfield \
-Wspir-compat \
-Wstatic-in-inline \
-Wstrict-potentially-direct-selector \
-Wstrict-prototypes \
-Wstrict-selector-match \
-Wsuggest-destructor-override \
-Wsuggest-override \
-Wsuper-class-method-mismatch \
-Wswitch-default \
-Wswitch-enum \
-Wtautological-constant-in-range-compare \
-Wthread-safety \
-Wthread-safety-beta \
-Wthread-safety-negative \
-Wthread-safety-verbose \
-Wunaligned-access \
-Wundeclared-selector \
-Wundef \
-Wunreachable-code \
-Wunused-macros \
-Wvariadic-macros \
-Wvla \
-Wzero-as-null-pointer-constant")

set(sources src/any.c src/bool.c src/byte.c src/char.c src/enum.c src/error.c src/number.c src/rune.c src/safe.c src/string.c)

include_directories(include)

add_library(the SHARED ${sources})
add_library(the_a STATIC ${sources})

if (MINGW OR UNIX)
  set(includedir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  set(libdir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  set(prefix "${CMAKE_INSTALL_PREFIX}")

  configure_file(libthe.pc.in libthe.pc @ONLY)
  configure_file(libthe-static.pc.in libthe-static.pc @ONLY)

  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(FILES LICENSE DESTINATION "${CMAKE_INSTALL_DOCDIR}")
  install(FILES "${PROJECT_BINARY_DIR}/libthe.pc" "${PROJECT_BINARY_DIR}/libthe-static.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  install(TARGETS the the_a LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif ()
