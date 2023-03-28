#include "s21_additional.h"
#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int sign = get_sign(value);
  int exp = get_exp(value);

  init_dec(sign, 0, 0, 0, 0, result);

  int flag = 0;

  if (exp > 28)
    flag = 1;
  else {
    if (exp == 0) *result = value;
    s21_decimal div_value = {0};
    init_dec(0, 0, 0, 0, 10, &div_value);

    while (exp != 0) {
      simple_div(value, div_value, result);
      value = *result;
      exp--;
    }
    set_exp(result, 0);
    set_sign(result, sign);
  }
  return flag;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 1;
  if (get_sign(value) == 0) {
    set_sign(&value, 1);
    *result = value;
    flag = 0;
  } else {
    set_sign(&value, 0);
    *result = value;
    flag = 0;
  }
  return flag;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 1;

  int exp = get_exp(value);
  if (exp < 28) {
    int sign = get_sign(value);
    s21_decimal div_value = {0};
    div_value.bits[0] = pow(10, exp);
    int mod = simple_fmod(value, div_value);
    s21_truncate(value, result);
    if (sign && mod > 0) result->bits[0] += 1;
    flag = 0;
  }
  return flag;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 1;

  int mod = 0;
  int exp = get_exp(value);
  int sign = get_sign(value);
  init_dec(sign, 0, 0, 0, 0, result);
  if (exp < 28) {
    if (exp > 0) {
      s21_decimal mod_val = {{10, 0, 0, 0}};
      for (int i = 0; i < exp; i++) {
        mod = simple_fmod(value, mod_val);
        simple_div(value, mod_val, &value);
      }
      *result = value;

      if (mod >= 5) result->bits[0] += 1;

    } else {
      *result = value;
    }
    set_exp(result, 0);
    set_sign(result, sign);
    flag = 0;
  }

  return flag;
}