/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_REFERENCE_H
#define THE_REFERENCE_H

/* See https://github.com/thelang-io/helpers for reference. */

/**
 * Macro that should be used to generate reference type.
 * @param underlying_type_name Name of the underlying type of the reference type.
 * @param underlying_type Underlying type of the reference type.
 */
#define THE_REFERENCE_DECLARE(underlying_type_name, underlying_type) \
  /** Object representation of the reference type. */ \
  typedef underlying_type *the_ref_##underlying_type_name##_t;

#endif
