#ifndef __UNIT_HPP__
# define __UNIT_HPP__

# include "color.hpp"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct {
	size_t  passed;
	size_t  failed;
}	t_xre_specs_state;

# define TIMEOUT_LIMIT 1 /* seconds */

extern t_xre_specs_state  __xre_specs__;

# define TEST_OK 1
# define TEST_KO 0
# define TEST_FUNCTION __attribute__((constructor))

#define __test_start__ \
	fprintf (stderr, "Launching %s\nFunction: %s%s%s\n", \
		__FILE__, BWHT, __PRETTY_FUNCTION__, CRESET); \

#define __test_end__   fprintf (stderr, "\n");

bool declare_test(bool (* test)(void), const char *title);

#define ASSERT_NUM_EQUAL(actual, expected, format_specifier) do { \
    __typeof__(actual) _actual = (actual); \
    __typeof__(expected) _expected = (expected); \
    if (_actual != _expected) { \
				printf( \
					"\n"\
					"  - line (%s%d%s)\n    +\tActual: %s%s%s == '" format_specifier "'\n" \
					"    - Expected: " format_specifier "' -> ", \
						BYEL, __LINE__, CRESET,\
						BRED, #actual,CRESET,   \
						actual,     \
						expected  \
				); \
				return (false); \
    } \
} while(0)

#define ASSERT_STR_EQUAL(actual, expected) do { \
  if (strcmp(actual, expected) != 0) { \
    printf( \
			"\n"\
			"  - line (%s%d%s)\n    +\tActual: '%s%s%s'\n" \
			"    - Expected: '%s' ", \
				BYEL, __LINE__, CRESET, \
				BRED, actual ,CRESET,   \
				expected  \
		); \
		return (false); \
	} \
} while(0)

#define ASSERT_IS_NULL(actual) do { \
  if (actual) { \
    printf( \
			"\n"\
			"  - line (%s%d%s)\n    +\tActual: %s%p%s\n" \
			"    - Expected: NULL ", \
				BYEL, __LINE__, CRESET, \
				BRED, actual ,CRESET   \
		); \
		return (false); \
	} \
} while(0)

#define ASSERT_IS_NOT_NULL(actual) do { \
  if (!actual) { \
    printf( \
			"\n"\
			"  - line (%s%d%s)\n "\
			"    - Expected: NOT NULL ", \
				BYEL, __LINE__, CRESET \
		); \
		return (false); \
	} \
} while(0)


#endif /* __UNIT_HPP__ */
