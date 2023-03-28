#include "test_decimal.h"

START_TEST(simple_trancate) {
  s21_decimal d1, d2;
  init_dec(0, 3, 0, 0, 7777, &d1);

  int res = s21_truncate(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 7);
  ck_assert_int_eq(res, 0);
}

START_TEST(trancate_eq_zero) {
  s21_decimal d1, d2;
  init_dec(0, 10, 0, 0, 7777, &d1);

  int res = s21_truncate(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 0);
  ck_assert_int_eq(res, 0);
}

START_TEST(trancate_exp_zero) {
  s21_decimal d1, d2;
  init_dec(0, 0, 0, 0, 7777, &d1);

  int res = s21_truncate(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 7777);
  ck_assert_int_eq(res, 0);
}

START_TEST(trancate_pass_through) {
  s21_decimal d1, d2;
  init_dec(0, 9, 0, 1, 0, &d1);

  int res = s21_truncate(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 4);
  ck_assert_int_eq(res, 0);
}

START_TEST(trancate_max) {
  s21_decimal d1, d2;
  init_dec(0, 28, 4294967295, 4294967295, 4294967295, &d1);

  int res = s21_truncate(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 7);
  ck_assert_int_eq(res, 0);
}

START_TEST(negate_positive) {
  s21_decimal d1, d2;
  init_dec(0, 28, 4294967295, 4294967295, 4294967295, &d1);

  int res = s21_negate(d1, &d2);

  ck_assert_int_eq(get_sign(d2), 1);
  ck_assert_int_eq(res, 0);
}

START_TEST(negate_negative) {
  s21_decimal d1, d2;
  init_dec(1, 28, 4294967295, 4294967295, 4294967295, &d1);

  int res = s21_negate(d1, &d2);

  ck_assert_int_eq(get_sign(d2), 0);
  ck_assert_int_eq(res, 0);
}

START_TEST(simple_floor) {
  s21_decimal d1, d2;
  init_dec(0, 1, 0, 0, 4294967295, &d1);

  int res = s21_floor(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 429496729);
  ck_assert_int_eq(res, 0);
}

START_TEST(simple_floor_negative) {
  s21_decimal d1, d2;
  init_dec(1, 1, 0, 0, 4294967295, &d1);

  int res = s21_floor(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 429496730);
  ck_assert_int_eq(res, 0);
}

START_TEST(floor_big_exp) {
  s21_decimal d1, d2;
  init_dec(0, 9, 0, 0, 4294967295, &d1);

  int res = s21_floor(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 4);
  ck_assert_int_eq(res, 0);
}

START_TEST(floor_big_exp_negative) {
  s21_decimal d1, d2;
  init_dec(1, 9, 0, 0, 4294967295, &d1);

  int res = s21_floor(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 5);
  ck_assert_int_eq(res, 0);
}

START_TEST(simple_round_up) {
  s21_decimal d1, d2;
  init_dec(0, 1, 0, 0, 4294967295, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 429496730);
  ck_assert_int_eq(res, 0);
}

START_TEST(simple_round_down) {
  s21_decimal d1, d2;
  init_dec(0, 1, 0, 0, 4294967294, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 429496729);
  ck_assert_int_eq(res, 0);
}

START_TEST(simple_round_up_negative) {
  s21_decimal d1, d2;
  init_dec(1, 1, 0, 0, 4294967295, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 429496730);
  ck_assert_int_eq(res, 0);
}

START_TEST(simple_round_down_negative) {
  s21_decimal d1, d2;
  init_dec(0, 1, 0, 0, 4294967294, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 429496729);
  ck_assert_int_eq(res, 0);
}

START_TEST(round_big_exp) {
  s21_decimal d1, d2;
  init_dec(0, 9, 0, 0, 4294967294, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 4);
  ck_assert_int_eq(res, 0);
}

START_TEST(round_big_exp_negative) {
  s21_decimal d1, d2;
  init_dec(1, 9, 0, 0, 3594967294, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 4);
  ck_assert_int_eq(res, 0);
}

START_TEST(round_exp_zero) {
  s21_decimal d1, d2;
  init_dec(0, 0, 0, 0, 15, &d1);

  int res = s21_round(d1, &d2);

  ck_assert_int_eq(d2.bits[0], 15);
  ck_assert_int_eq(res, 0);
}

Suite *suite_s21_other() {
  Suite *s = suite_create("S21_OTHER");
  TCase *test_case = tcase_create("S21_OTHER");

  if (s != NULL && test_case != NULL) {
    tcase_add_test(test_case, simple_trancate);
    tcase_add_test(test_case, trancate_eq_zero);
    tcase_add_test(test_case, trancate_pass_through);
    tcase_add_test(test_case, trancate_max);
    tcase_add_test(test_case, negate_positive);
    tcase_add_test(test_case, negate_negative);
    tcase_add_test(test_case, simple_floor);
    tcase_add_test(test_case, simple_floor_negative);
    tcase_add_test(test_case, floor_big_exp);
    tcase_add_test(test_case, floor_big_exp_negative);
    tcase_add_test(test_case, simple_round_up);
    tcase_add_test(test_case, simple_round_down);
    tcase_add_test(test_case, simple_round_up_negative);
    tcase_add_test(test_case, simple_round_down_negative);
    tcase_add_test(test_case, round_big_exp);
    tcase_add_test(test_case, round_big_exp_negative);
    tcase_add_test(test_case, trancate_exp_zero);
    tcase_add_test(test_case, round_exp_zero);

    suite_add_tcase(s, test_case);
  }

  return s;
}