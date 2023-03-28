#include "test_decimal.h"

START_TEST(simple_add) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 22222, 2152, 15, &d1);
  init_dec(0, 0, 45435, 43543, 24, &d2);

  int res = s21_add(d1, d2, &d3);

  ck_assert_int_eq(d3.bits[0], 15 + 24);
  ck_assert_int_eq(d3.bits[1], 2152 + 43543);
  ck_assert_int_eq(d3.bits[2], 22222 + 45435);
  ck_assert_int_eq(res, 0);
}

START_TEST(add_great_mantissa) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 4294967295, 4294967295, 4294967294, &d1);
  init_dec(0, 7, 0, 0, 1, &d2);

  int res = s21_add(d1, d2, &d3);

  ck_assert_int_eq(res, 0);
}

START_TEST(add_diff_exp) {
  s21_decimal d1, d2, d3;
  init_dec(0, 2, 0, 0, 15, &d1);
  init_dec(0, 6, 0, 0, 173, &d2);

  int res = s21_add(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 150000 + 173);
  ck_assert_int_eq(get_exp(d3), 6);
  ck_assert_int_eq(res, 0);
}

START_TEST(add_pass_through) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 1, 4294967295, &d1);
  init_dec(0, 0, 0, 4294967295, 1, &d2);

  int res = s21_add(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 0);
  ck_assert_int_eq(d3.bits[1], 1);
  ck_assert_int_eq(d3.bits[2], 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(add_diff_sign) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 0, 172, &d1);
  init_dec(1, 0, 0, 0, 12, &d2);

  int res = s21_add(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 160);
  ck_assert_int_eq(get_sign(d3), 0);
  ck_assert_int_eq(res, 0);
}

START_TEST(add_both_minus) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 0, 0, 172, &d1);
  init_dec(1, 0, 0, 0, 12, &d2);

  int res = s21_add(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 184);
  ck_assert_int_eq(get_sign(d3), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(add_greater) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 4294967295, 4294967295, 4294967295, &d1);
  init_dec(0, 0, 0, 0, 1, &d2);

  int res = s21_add(d1, d2, &d3);
  ck_assert_int_eq(res, 1);
}

START_TEST(simple_sub) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 422222, 215233, 153, &d1);
  init_dec(0, 0, 45435, 43543, 24, &d2);

  int res = s21_sub(d1, d2, &d3);

  ck_assert_int_eq(d3.bits[0], 153 - 24);
  ck_assert_int_eq(d3.bits[1], 215233 - 43543);
  ck_assert_int_eq(d3.bits[2], 422222 - 45435);
  ck_assert_int_eq(res, 0);
}

START_TEST(sub_diff_exp) {
  s21_decimal d1, d2, d3;
  init_dec(0, 2, 0, 0, 15, &d1);
  init_dec(0, 6, 0, 0, 173, &d2);

  int res = s21_sub(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 150000 - 173);
  ck_assert_int_eq(get_exp(d3), 6);
  ck_assert_int_eq(res, 0);
}

START_TEST(sub_pass_through) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 1, 0, &d1);
  init_dec(0, 0, 0, 0, 4294967295, &d2);

  int res = s21_sub(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 1);
  ck_assert_int_eq(d3.bits[1], 0);
  ck_assert_int_eq(d3.bits[2], 0);
  ck_assert_int_eq(res, 0);
}

START_TEST(sub_diff_sign) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 0, 172, &d1);
  init_dec(1, 0, 0, 0, 12, &d2);

  int res = s21_sub(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 184);
  ck_assert_int_eq(get_sign(d3), 0);
  ck_assert_int_eq(res, 0);
}

START_TEST(sub_both_minus) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 0, 0, 172, &d1);
  init_dec(1, 0, 0, 0, 12, &d2);

  int res = s21_sub(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 160);
  ck_assert_int_eq(get_sign(d3), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(sub_greater) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 4294967295, 4294967295, 4294967295, &d1);
  init_dec(1, 0, 0, 0, 1, &d2);

  int res = s21_sub(d1, d2, &d3);
  ck_assert_int_eq(res, 1);
}

START_TEST(simple_mul) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 10, 11, &d1);
  init_dec(0, 0, 0, 7, 24, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(res, 0);
}

START_TEST(mul_great_mantissa) {
  s21_decimal d1, d2, d3;
  init_dec(0, 27, 0, 0, 1, &d1);
  init_dec(0, 5, 0, 0, 2, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(res, 0);
}

START_TEST(mul_diff_sign) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 0, 5, 11, &d1);
  init_dec(0, 0, 0, 435, 24, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(get_sign(d3), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(mul_greater) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 3432, 10, 11, &d1);
  init_dec(0, 0, 454, 7, 24, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(res, 1);
}

START_TEST(mul_less) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 3432, 10, 11, &d1);
  init_dec(0, 0, 454, 7, 24, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(res, 2);
}

START_TEST(mul_both_minus) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 0, 0, 17, &d1);
  init_dec(1, 0, 0, 0, 2, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(get_sign(d3), 0);
  ck_assert_int_eq(d3.bits[0], 34);
}

START_TEST(mul_diff_exp) {
  s21_decimal d1, d2, d3;
  init_dec(0, 3, 0, 0, 17, &d1);
  init_dec(0, 11, 0, 0, 2, &d2);

  int res = s21_mul(d1, d2, &d3);
  ck_assert_int_eq(get_exp(d3), 14);
  ck_assert_int_eq(res, 0);
}

START_TEST(simplee_div) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 0, 256, &d1);
  init_dec(0, 0, 0, 0, 2, &d2);

  int res = s21_div(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 128);
  ck_assert_int_eq(res, 0);
}

START_TEST(div_diff_exp) {
  s21_decimal d1, d2, d3;
  init_dec(0, 11, 0, 0, 256, &d1);
  init_dec(0, 3, 0, 0, 2, &d2);

  int res = s21_div(d1, d2, &d3);
  ck_assert_int_eq(get_exp(d3), 8);
  ck_assert_int_eq(res, 0);
}

START_TEST(div_diff_sign) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 0, 0, 256, &d1);
  init_dec(0, 0, 0, 0, 2, &d2);

  int res = s21_div(d1, d2, &d3);
  ck_assert_int_eq(get_sign(d3), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(div_both_minus) {
  s21_decimal d1, d2, d3;
  init_dec(1, 0, 0, 0, 256, &d1);
  init_dec(1, 0, 0, 0, 2, &d2);

  int res = s21_div(d1, d2, &d3);
  ck_assert_int_eq(get_sign(d3), 0);
  ck_assert_int_eq(res, 0);
}

START_TEST(div_by_zero) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 0, 256, &d1);
  init_dec(0, 0, 0, 0, 0, &d2);

  int res = s21_div(d1, d2, &d3);
  ck_assert_int_eq(res, 3);
}

START_TEST(simple_mod) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 0, 256, &d1);
  init_dec(0, 0, 0, 0, 250, &d2);

  int res = s21_mod(d1, d2, &d3);
  ck_assert_int_eq(d3.bits[0], 6);
  ck_assert_int_eq(res, 0);
}

START_TEST(mod_diff_exp) {
  s21_decimal d1, d2, d3;
  init_dec(0, 11, 0, 0, 256, &d1);
  init_dec(0, 3, 0, 0, 250, &d2);

  int res = s21_mod(d1, d2, &d3);
  ck_assert_int_eq(get_exp(d3), 11);
  ck_assert_int_eq(res, 0);
}

START_TEST(mod_by_zero) {
  s21_decimal d1, d2, d3;
  init_dec(0, 0, 0, 0, 256, &d1);
  init_dec(0, 0, 0, 0, 0, &d2);

  int res = s21_mod(d1, d2, &d3);
  ck_assert_int_eq(res, 3);
}

Suite *suite_s21_arithmetic() {
  Suite *s = suite_create("S21_ARITHMETIC");
  TCase *test_case = tcase_create("S21_ARITHMETIC");

  if (s != NULL && test_case != NULL) {
    tcase_add_test(test_case, simple_add);
    tcase_add_test(test_case, add_diff_exp);
    tcase_add_test(test_case, add_pass_through);
    tcase_add_test(test_case, add_diff_sign);
    tcase_add_test(test_case, add_both_minus);
    tcase_add_test(test_case, add_greater);
    tcase_add_test(test_case, simple_sub);
    tcase_add_test(test_case, sub_diff_exp);
    tcase_add_test(test_case, sub_pass_through);
    tcase_add_test(test_case, sub_diff_sign);
    tcase_add_test(test_case, sub_both_minus);
    tcase_add_test(test_case, sub_greater);
    tcase_add_test(test_case, simple_mul);
    tcase_add_test(test_case, mul_diff_sign);
    tcase_add_test(test_case, mul_greater);
    tcase_add_test(test_case, mul_less);
    tcase_add_test(test_case, mul_both_minus);
    tcase_add_test(test_case, mul_diff_exp);
    tcase_add_test(test_case, simplee_div);
    tcase_add_test(test_case, div_diff_exp);
    tcase_add_test(test_case, div_diff_sign);
    tcase_add_test(test_case, div_both_minus);
    tcase_add_test(test_case, div_by_zero);
    tcase_add_test(test_case, simple_mod);
    tcase_add_test(test_case, mod_diff_exp);
    tcase_add_test(test_case, mod_by_zero);
    tcase_add_test(test_case, mul_great_mantissa);
    tcase_add_test(test_case, add_great_mantissa);

    suite_add_tcase(s, test_case);
  }

  return s;
}