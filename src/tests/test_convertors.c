#include "test_decimal.h"

START_TEST(from_int_to_decimal) {
  s21_decimal d1;
  int tmp = 15;

  int res = s21_from_int_to_decimal(tmp, &d1);
  ck_assert_int_eq(d1.bits[0], 15);
  ck_assert_int_eq(res, 0);
}

START_TEST(from_int_to_decimal_negative) {
  s21_decimal d1;
  int tmp = -15;

  int res = s21_from_int_to_decimal(tmp, &d1);
  ck_assert_int_eq(d1.bits[0], 15);
  ck_assert_int_eq(get_sign(d1), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(from_int_to_decimal_max) {
  s21_decimal d1;
  int tmp = 2147483647;

  int res = s21_from_int_to_decimal(tmp, &d1);
  ck_assert_int_eq(d1.bits[0], 2147483647);
  ck_assert_int_eq(res, 0);
}

START_TEST(from_int_to_decimal_min) {
  s21_decimal d1;
  int tmp = -2147483645;

  int res = s21_from_int_to_decimal(tmp, &d1);
  ck_assert_int_eq(d1.bits[0], 2147483645);
  ck_assert_int_eq(get_sign(d1), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(from_decimal_to_int) {
  s21_decimal d1;
  init_dec(0, 0, 0, 0, 2568, &d1);

  int tmp;
  int res = s21_from_decimal_to_int(d1, &tmp);

  ck_assert_int_eq(tmp, 2568);
  ck_assert_int_eq(res, 0);
}

START_TEST(from_decimal_to_int_overflow) {
  s21_decimal d1;
  init_dec(0, 0, 0, 1, 2568, &d1);

  int tmp;
  int res = s21_from_decimal_to_int(d1, &tmp);

  ck_assert_int_eq(res, 1);
}

START_TEST(from_decimal_to_int_positive) {
  s21_decimal d1;
  init_dec(0, 0, 0, 0, 17, &d1);
  int tmp;
  int res = s21_from_decimal_to_int(d1, &tmp);

  ck_assert_int_eq(res, 0);
}

START_TEST(from_decimal_to_int_negative) {
  s21_decimal d1;
  init_dec(1, 0, 0, 0, 33, &d1);
  int tmp;
  int res = s21_from_decimal_to_int(d1, &tmp);

  ck_assert_int_eq(res, 0);
}

START_TEST(from_decimal_to_int_exp) {
  s21_decimal d1;
  init_dec(0, 1, 0, 0, 333, &d1);
  int tmp;
  int res = s21_from_decimal_to_int(d1, &tmp);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(tmp, 33);
}

START_TEST(from_decimal_to_float) {
  s21_decimal d1;
  init_dec(0, 0, 0, 0, 333, &d1);
  float tmp;
  int res = s21_from_decimal_to_float(d1, &tmp);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(tmp, 333);
}

START_TEST(from_decimal_to_float_exp) {
  s21_decimal d1;
  init_dec(0, 2, 0, 0, 333, &d1);
  float tmp;
  int res = s21_from_decimal_to_float(d1, &tmp);

  ck_assert_int_eq(res, 0);
}

START_TEST(from_decimal_to_float_overflow) {
  s21_decimal d1;
  init_dec(0, 0, 0, 1, 333, &d1);
  float tmp;
  int res = s21_from_decimal_to_float(d1, &tmp);

  ck_assert_int_eq(res, 1);
}

START_TEST(from_float_to_decimal) {
  float tmp = 411;
  s21_decimal d1;

  int res = s21_from_float_to_decimal(tmp, &d1);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(d1.bits[0], 411);
}

START_TEST(from_float_to_big) {
  float tmp = 1E8;
  s21_decimal d1;

  int res = s21_from_float_to_decimal(tmp, &d1);

  ck_assert_int_eq(res, 0);
}

START_TEST(from_float_to_decimal_exp) {
  float tmp = 411.23;
  s21_decimal d1;

  int res = s21_from_float_to_decimal(tmp, &d1);
  ck_assert_int_eq(res, 0);
}

START_TEST(from_float_to_decimal_negative) {
  float tmp = -411.23;
  s21_decimal d1;

  int res = s21_from_float_to_decimal(tmp, &d1);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(get_sign(d1), 1);
}

Suite *suite_s21_convertors() {
  Suite *s = suite_create("S21_CONVERTORS");
  TCase *test_case = tcase_create("S21_CONVERTORS");

  if (s != NULL && test_case != NULL) {
    tcase_add_test(test_case, from_int_to_decimal);
    tcase_add_test(test_case, from_int_to_decimal_negative);
    tcase_add_test(test_case, from_int_to_decimal_max);
    tcase_add_test(test_case, from_int_to_decimal_min);
    tcase_add_test(test_case, from_decimal_to_int);
    tcase_add_test(test_case, from_decimal_to_int_overflow);
    tcase_add_test(test_case, from_decimal_to_int_positive);
    tcase_add_test(test_case, from_decimal_to_int_negative);
    tcase_add_test(test_case, from_decimal_to_int_exp);
    tcase_add_test(test_case, from_decimal_to_float);
    tcase_add_test(test_case, from_decimal_to_float_exp);
    tcase_add_test(test_case, from_decimal_to_float_overflow);
    tcase_add_test(test_case, from_float_to_decimal);
    tcase_add_test(test_case, from_float_to_decimal_exp);
    tcase_add_test(test_case, from_float_to_decimal_negative);
    tcase_add_test(test_case, from_float_to_big);

    suite_add_tcase(s, test_case);
  }

  return s;
}