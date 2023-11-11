#include "unit.hpp"
#include <stdio.h>

t_xre_specs_state  __xre_specs__;

int main(void) {
	__xre_specs__.passed = 0,
	__xre_specs__.failed = 0,
	fprintf(stdout,
			"TESTS SUMMARY:\n"
			"   tests failed: %zu\n"
			"   tests passed: %zu\n"
			"          total: %zu\n"
			"\n",
		__xre_specs__.failed,
		__xre_specs__.passed,
		__xre_specs__.failed + __xre_specs__.passed
	);
	return (0); }