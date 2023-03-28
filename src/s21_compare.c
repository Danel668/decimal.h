#include "s21_additional.h"
#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  for (int i = 0; i < 4; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      result = 0;
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  long_dec long_value_1, long_value_2;
  decimalToLongDecimal(value_1, &long_value_1);
  decimalToLongDecimal(value_2, &long_value_2);
  if (getsign(value_1) < getsign(value_2)) {
    if (!(s21_greater_long_without_sign(long_value_1, long_value_2) == 2 &&
          value_1.bits[0] == 0 && value_1.bits[1] == 0 &&
          value_1.bits[2] == 0)) {
      result = 1;
    }
  } else if (getsign(value_1) == getsign(value_2)) {
    if (getsign(value_1) == 0) {
      if (s21_greater_long_without_sign(long_value_1, long_value_2) == 0) {
        result = 1;
      } else {
        result = 0;
      }
    } else {
      if (s21_greater_long_without_sign(long_value_1, long_value_2) == 1) {
        result = 1;
      }
    }
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_2, value_1);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}