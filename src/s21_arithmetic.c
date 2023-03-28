#include "s21_additional.h"
#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  long_dec ld1, ld2, ld3;
  dec_to_longdec(value_1, &ld1);
  dec_to_longdec(value_2, &ld2);
  normalize_long(&ld1, &ld2);
  add(ld1, ld2, &ld3);
  longdec_to_dec(ld3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  long_dec ld1, ld2, ld3;
  dec_to_longdec(value_1, &ld1);
  dec_to_longdec(value_2, &ld2);
  normalize_long(&ld1, &ld2);
  sub(ld1, ld2, &ld3);
  longdec_to_dec(ld3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return res;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  long_dec ld1, ld2, ld3;
  dec_to_longdec(value_1, &ld1);
  dec_to_longdec(value_2, &ld2);
  mul(ld1, ld2, &ld3);
  longdec_to_dec(ld3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return res;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  long_dec ld1, ld2, ld3;
  dec_to_longdec(value_1, &ld1);
  dec_to_longdec(value_2, &ld2);
  normalize_long(&ld1, &ld2);
  mod(ld1, ld2, &ld3);
  longdec_to_dec(ld3, result);
  if (get_bit(*result, 96))
    init_dec(get_sign(*result), get_exp(*result), 0, 0, 0, result);

  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return (mantissa_is_zero(ld2) ? 3 : res);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  long_dec ld1, ld2, ld3;
  dec_to_longdec(value_1, &ld1);
  dec_to_longdec(value_2, &ld2);
  div_dec(ld1, ld2, &ld3);
  longdec_to_dec(ld3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return (mantissa_is_zero(ld2) ? 3 : res);
}
