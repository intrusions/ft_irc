#include "unit.hpp"

static bool __test_001__(void) {

	return (true);
}

static bool __test_002__(void) {

	return (true);
}

TEST_FUNCTION void reply_specs(void) {
	__test_start__;

  declare_test(&__test_001__, "Test de test");
  declare_test(&__test_002__, "Test de test 2");
	__test_end__;
}