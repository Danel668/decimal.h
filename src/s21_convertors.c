#include "s21_additional.h"
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 1;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (src < 0) {
    set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  flag = 0;
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 1;
  if (get_exp(src) > 0) {
    s21_decimal result = {{0}};
    s21_truncate(src, &result);
    src = result;
  }
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    if (src.bits[0] > INT32_MAX) {
      flag = 1;
    } else if (get_sign(src) == 0) {
      *dst = src.bits[0];
      flag = 0;
    } else if (get_sign(src) == 1) {
      *dst = -src.bits[0];
      flag = 0;
    }
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = 0;
  int decimal_exp = 0;
  double result = 0;

  for (int i = 0; i < 32; i++) {
    if (get_bit(src, i) == 1) {
      result += pow(2, i);
    }
  }

  if (src.bits[1] != 0 || src.bits[2] != 0)
    flag = 1;
  else {
    decimal_exp = get_exp(src);
    while (decimal_exp > 0) {
      result /= 10;
      decimal_exp--;
    }
    if (get_sign(src) == 1) {
      result *= -1;
    }
  }

  *dst = (float)result;

  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  int ex = 0;
  double f = (double)src;
  if (fabs(src) < 1e-28) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src != 0.f) flag = 1;
    return flag;
  }
  if (fabs(src) > 7922816251426433759354395033E1 || src == -__builtin_inff()) {
    flag = 1;
  }
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (src < 0) {
    f *= -1;
    set_sign(dst, 1);
  }
  if (fabs(src) < 1e7) {
    for (int i = 0; i < 28; i++) {
      if (f > 999999) {
        break;
      }
      f *= 10;
      ex++;
    }
    f = roundf(f);
    while (fmod(f, 10.) == 0) {
      f /= 10;
      ex--;
    }
    set_exp(dst, ex);
    dst->bits[0] = roundf(f);
  } else {
    double d = (double)f;
    while (d > 9999999) {
      d *= 0.1;
      ex++;
    }
    s21_decimal dec_f = {{(int)round(d), 0, 0, 0}};
    s21_decimal dec_exp = {{10, 0, 0, 0}};
    for (int i = 0; i < ex - 1; i++) {
      s21_decimal dec = {{10, 0, 0, 0}};
      s21_decimal temp = {{0, 0, 0, 0}};
      s21_mul(dec_exp, dec, &temp);
      dec_exp = temp;
    }
    s21_mul(dec_exp, dec_f, dst);
  }

  return flag;
}