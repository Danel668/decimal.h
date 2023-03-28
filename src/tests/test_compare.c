#include "test_decimal.h"

START_TEST(is_equal) {
  s21_decimal d1, d2;
  init_dec(1, 3, 166, 91, 2567, &d1);
  init_dec(1, 3, 166, 91, 2567, &d2);

  int res = s21_is_equal(d1, d2);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_not_equal) {
  s21_decimal d1, d2;
  init_dec(1, 3, 166, 991, 2567, &d1);
  init_dec(1, 3, 166, 91, 2567, &d2);

  int res = s21_is_not_equal(d1, d2);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_greater_mantissa) {
  s21_decimal d1, d2;
  init_dec(1, 3, 166, 991, 2568, &d1);
  init_dec(1, 3, 166, 911, 2567, &d2);

  int res = s21_is_greater(d1, d2);
  ck_assert_int_eq(res, 0);
}

START_TEST(is_greater_sign) {
  s21_decimal d1, d2;
  init_dec(0, 3, 166, 991, 2568, &d1);
  init_dec(1, 3, 166, 911, 2569, &d2);

  int res = s21_is_greater(d1, d2);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_greater_exp) {
  s21_decimal d1, d2;
  init_dec(0, 2, 166, 991, 2568, &d1);
  init_dec(1, 3, 166, 911, 2568, &d2);

  int res = s21_is_greater(d1, d2);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_greater_or_eq) {
  s21_decimal d1, d2;
  init_dec(0, 3, 166, 991, 777, &d1);
  init_dec(0, 3, 166, 911, 777, &d2);

  s21_decimal d3, d4;
  init_dec(0, 3, 99999, 991, 777, &d3);
  init_dec(0, 3, 99999, 991, 777, &d4);

  s21_decimal d5, d6;
  init_dec(0, 3, 99999, 991, 777, &d5);
  init_dec(0, 4, 99999, 991, 777, &d6);

  int res = s21_is_greater_or_equal(d1, d2);
  int res4 = s21_is_greater_or_equal(d2, d1);
  int res2 = s21_is_greater_or_equal(d3, d4);
  int res3 = s21_is_greater_or_equal(d6, d5);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
}

START_TEST(is_less_mantissa) {
  s21_decimal d1, d2;
  init_dec(1, 3, 166, 991, 2568, &d1);
  init_dec(1, 3, 166, 911, 2567, &d2);

  int res = s21_is_less(d1, d2);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_less_sign) {
  s21_decimal d1, d2;
  init_dec(0, 3, 166, 991, 2568, &d1);
  init_dec(1, 3, 166, 911, 2569, &d2);

  int res = s21_is_less(d2, d1);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_less_exp) {
  s21_decimal d1, d2;
  init_dec(0, 2, 166, 991, 2568, &d1);
  init_dec(1, 3, 166, 911, 2568, &d2);

  int res = s21_is_less(d2, d1);
  ck_assert_int_eq(res, 1);
}

START_TEST(is_less_or_eq) {
  s21_decimal d1, d2;
  init_dec(1, 3, 166, 991, 777, &d1);
  init_dec(1, 3, 166, 991, 777, &d2);

  s21_decimal d3, d4;
  init_dec(0, 3, 166, 991, 777, &d3);
  init_dec(1, 3, 99999, 911, 0, &d4);

  s21_decimal d5, d6;
  init_dec(0, 3, 166, 991, 777, &d5);
  init_dec(0, 4, 166, 991, 777, &d6);

  int res = s21_is_less_or_equal(d2, d1);
  int res2 = s21_is_less_or_equal(d4, d3);
  int res4 = s21_is_less_or_equal(d3, d4);
  int res3 = s21_is_less_or_equal(d5, d6);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
}

Suite *suite_s21_compare() {
  Suite *s = suite_create("S21_COMPARE");
  TCase *test_case = tcase_create("S21_COMPARE");

  if (s != NULL && test_case != NULL) {
    tcase_add_test(test_case, is_equal);
    tcase_add_test(test_case, is_not_equal);
    tcase_add_test(test_case, is_greater_mantissa);
    tcase_add_test(test_case, is_greater_sign);
    tcase_add_test(test_case, is_greater_exp);
    tcase_add_test(test_case, is_greater_or_eq);
    tcase_add_test(test_case, is_less_mantissa);
    tcase_add_test(test_case, is_less_sign);
    tcase_add_test(test_case, is_less_exp);
    tcase_add_test(test_case, is_less_or_eq);
    suite_add_tcase(s, test_case);
  }

  return s;
}
