#ifndef S21_ADDITIONAL_H
#define S21_ADDITIONAL_H

#include "s21_decimal.h"

typedef struct {
  unsigned int bits[6];
  int8_t exp;
  bool sign;
} long_dec;

int get_bit(s21_decimal d, int position);
void set_bit(s21_decimal *d, int position, int digit);
int get_exp(s21_decimal d);
void set_exp(s21_decimal *d, int exp);
int get_sign(s21_decimal d);
void set_sign(s21_decimal *d, int sign);

int get_bit_long(long_dec ld, int position);
void set_bit_long(long_dec *ld, int position, int digit);
int get_exp_long(long_dec ld);
void set_exp_long(long_dec *ld, int exp);
int get_sign_long(long_dec ld);
void set_sign_long(long_dec *ld, int sign);

int add_bits(int bit1, int bit2, int *carry);
int sub_bits(int bit1, int bit2, int *carry);

int mantissa_is_zero(long_dec ld1);
int mantissa_is_equal(long_dec ld1, long_dec ld2);
int mantissa_is_not_equal(long_dec ld1, long_dec ld2);
int mantissa_is_greater_long(long_dec ld1, long_dec ld2);
int mantissa_is_greater_or_equal(long_dec ld1, long_dec ld2);
int mantissa_is_less(long_dec ld1, long_dec ld2);
int mantissa_is_less_or_equal(long_dec ld1, long_dec ld2);

void add(long_dec ld1, long_dec ld2, long_dec *result);
void sub(long_dec ld1, long_dec ld2, long_dec *result);
void mul(long_dec ld1, long_dec ld2, long_dec *result);
void mod(long_dec ld1, long_dec ld2, long_dec *result);
void div_dec(long_dec ld1, long_dec ld2, long_dec *result);
void div_int(long_dec ld1, long_dec ld2, long_dec *result);

void dec_to_longdec(s21_decimal d, long_dec *result);
void longdec_to_dec(long_dec value, s21_decimal *result);

void copy_longdec(long_dec ld, long_dec *result);
void copy_dec(s21_decimal *result, s21_decimal d);

void add_exp(long_dec value, long_dec *result);
void sub_exp(long_dec value, long_dec *result);

void round_dec(long_dec value, long_dec *result);
void round_bank(long_dec value, long_dec *result);

int simple_div(s21_decimal d1, s21_decimal d2, s21_decimal *result);
int simple_fmod(s21_decimal d1, s21_decimal d2);

void mantissa_shift_left_long(long_dec ld, long_dec *result);
void mantissa_shift_left(s21_decimal *value);

void normalize_long(long_dec *ld1, long_dec *ld2);

int mantissa_is_greater(s21_decimal value_1, s21_decimal value_2);

void init_dec(int sign, int exp, unsigned int b2, unsigned int b1,
              unsigned int b0, s21_decimal *result);

// additional_for_compare
int s21_get_bit(s21_decimal value, int index);
void s21_set_bit(s21_decimal *value, int index, int bit_value);
int getpow(s21_decimal value_1);
void nullValue(s21_decimal *value);
void putpow(s21_decimal *value_1, int power);
void nullValueLong(long_dec *value);
int getsign(s21_decimal value_1);
int s21_get_bit_long(long_dec value, int index);
void s21_set_bit_long(long_dec *value, int index, int bit_value);
int decimalToLongDecimal(s21_decimal value, long_dec *result);
int mul_long(long_dec value_1, long_dec value_2, long_dec *result);
int shiftLeft_long(long_dec value, int shiftValue, long_dec *shiftedValue);

int sumLong(long_dec value_1, long_dec value_2, long_dec *value);

void put_llintInLongDecimal(long_dec *value, long long number);

int getsign_long(long_dec value_1);
void mulSign_long(long_dec value_1, long_dec value_2, long_dec *result);
int s21_greater_long_without_sign(long_dec value_1, long_dec value_2);

#endif  // S21_ADDITIONAL_H