#include "unit.hpp"
#include <stdio.h>

int main(void) {
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