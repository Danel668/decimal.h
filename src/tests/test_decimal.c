#include "test_decimal.h"

static int run_test_suite(Suite *test_suite) {
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = srunner_create(test_suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed);
}

int main(void) {
  int number_failed = 0;
  Suite *suite_array[] = {suite_s21_arithmetic(),
                          suite_s21_compare(),
                          suite_s21_other(),
                          suite_s21_convertors(),
                          suite_mul(),
                          suite_is_greater(),
                          suite_is_less(),
                          suite_from_float_to_decimal(),
                          NULL};

  for (size_t i = 0; suite_array[i]; ++i) {
    number_failed += run_test_suite(suite_array[i]);
  }

  return (number_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
