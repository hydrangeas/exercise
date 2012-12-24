#include <CUnit/CUnit.h>
#include <CUnit/Console.h>

extern int coinCount(const int);

void test_coinCount();

int
main(int argc, char* argv[]) {
  CU_pSuite test_suite;

  CU_initialize_registry();
  test_suite = CU_add_suite ("TestSuite", NULL, NULL);
  CU_add_test (test_suite, "test to a function of coinCount", test_coinCount);
  CU_console_run_tests();
  CU_cleanup_registry();
  return 0;
}

void
test_coinCount() {
  CU_ASSERT (1 == 1);
}

