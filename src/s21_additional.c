#include "s21_additional.h"

int get_sign(s21_decimal d) { return (d.bits[3] >> 31 ? 1 : 0); }

void set_sign(s21_decimal *d, int sign) {
  int mask = 1U << 31;
  if (sign == 1)
    d->bits[3] |= mask;
  else
    d->bits[3] &= ~mask;
}

int get_exp(s21_decimal d) { return ((d.bits[3] >> 16) & 0x7F); }

void set_exp(s21_decimal *d, int exp) {
  if (exp >= 0 && exp <= 28) {
    int sign = get_sign(*d);
    d->bits[3] = exp << 16;
    set_sign(d, sign);
  }
}

int get_bit(s21_decimal d, int position) {
  return (d.bits[position / 32] >> (position % 32)) & 1U;
}

void set_bit(s21_decimal *d, int position, int digit) {
  int mask = 1U << (position % 32);
  if (digit == 1)
    d->bits[position / 32] |= mask;
  else
    d->bits[position / 32] &= ~mask;
}

int get_bit_long(long_dec ld, int position) {
  return (ld.bits[position / 32] >> (position % 32)) & 1U;
}

void set_bit_long(long_dec *ld, int position, int digit) {
  int mask = 1U << (position % 32);
  if (digit == 1)
    ld->bits[position / 32] |= mask;
  else
    ld->bits[position / 32] &= ~mask;
}

int get_sign_long(long_dec ld) { return ld.sign; }

void set_sign_long(long_dec *ld, int sign) { ld->sign = sign; }

int get_exp_long(long_dec ld) { return ld.exp; }

void set_exp_long(long_dec *ld, int exp) { ld->exp = exp; }

void dec_to_longdec(s21_decimal d, long_dec *result) {
  for (int i = 0; i < 6; i++) result->bits[i] = 0;
  result->exp = 0;
  result->sign = 0;
  set_sign_long(result, get_sign(d));
  set_exp_long(result, get_exp(d));
  set_bit_long(result, 96, get_bit(d, 96));
  result->bits[0] = d.bits[0];
  result->bits[1] = d.bits[1];
  result->bits[2] = d.bits[2];
}

void copy_longdec(long_dec ld, long_dec *result) {
  for (int i = 0; i < 6; i++) result->bits[i] = ld.bits[i];
  result->exp = ld.exp;
  result->sign = ld.sign;
}

void copy_dec(s21_decimal *result, s21_decimal d) {
  for (int i = 0; i <= 3; i++) result->bits[i] = d.bits[i];
}

int mantissa_is_greater_long(long_dec ld1, long_dec ld2) {
  int flag = 0;
  for (int i = 191; i >= 0; i--)
    if (get_bit_long(ld1, i) != get_bit_long(ld2, i)) {
      flag = get_bit_long(ld1, i);
      break;
    }
  return flag;
}

int mantissa_is_less(long_dec ld1, long_dec ld2) {
  return mantissa_is_greater_long(ld2, ld1);
}

int mantissa_is_equal(long_dec ld1, long_dec ld2) {
  int flag = 1;
  for (int i = 0; i < 192; i++) {
    if (get_bit_long(ld1, i) != get_bit_long(ld2, i)) {
      flag = 0;
      break;
    }
  }
  return flag;
}

int mantissa_is_less_or_equal(long_dec ld1, long_dec ld2) {
  return mantissa_is_less(ld1, ld2) || mantissa_is_equal(ld1, ld2);
}

int mantissa_is_not_equal(long_dec ld1, long_dec ld2) {
  return !mantissa_is_equal(ld1, ld2);
}

int mantissa_is_greater_or_equal(long_dec ld1, long_dec ld2) {
  return mantissa_is_greater_long(ld1, ld2) || mantissa_is_equal(ld1, ld2);
}

int add_bits(int bit1, int bit2, int *carry) {
  int bit3 = bit1 + bit2 + *carry;
  if (bit3 == 0)
    *carry = 0;
  else if (bit3 == 1)
    *carry = 0;
  else if (bit3 == 2) {
    *carry = 1;
    bit3 = 0;
  } else if (bit3 == 3) {
    bit3 = 1;
    *carry = 1;
  }

  return bit3;
}

int sub_bits(int bit1, int bit2, int *carry) {
  if (*carry) bit1 = !bit1;
  if (*carry && !bit1) *carry = 0;
  if (bit1 - bit2 < 0) *carry = 1;
  return (abs(bit1 - bit2));
}

void add(long_dec ld1, long_dec ld2, long_dec *result) {
  if (get_sign_long(ld1) != get_sign_long(ld2)) {
    set_sign_long(&ld2, get_sign_long(ld1));
    return sub(ld1, ld2, result);
  }

  long_dec sum = {0};
  set_sign_long(&sum, get_sign_long(ld1));
  set_exp_long(&sum, get_exp_long(ld1));

  int temp = 0;
  for (int i = 0; i < 192; i++) {
    int b1 = get_bit_long(ld1, i);
    int b2 = get_bit_long(ld2, i);
    int b3 = add_bits(b1, b2, &temp);
    set_bit_long(&sum, i, b3);
  }
  copy_longdec(sum, result);
}

void sub(long_dec ld1, long_dec ld2, long_dec *result) {
  if (get_sign_long(ld1) != get_sign_long(ld2)) {
    set_sign_long(&ld2, get_sign_long(ld1));
    return add(ld1, ld2, result);
  }

  long_dec diff = {0};
  set_sign_long(&diff, get_sign_long(ld1));
  set_exp_long(&diff, get_exp_long(ld1));

  if (mantissa_is_greater_long(ld2, ld1)) {
    int temp = get_exp_long(ld1);
    set_exp_long(&ld1, get_exp_long(ld2));
    set_exp_long(&ld1, temp);
    for (int i = 0; i < 6; i++) {
      temp = ld1.bits[i];
      ld1.bits[i] = ld2.bits[i];
      ld2.bits[i] = temp;
    }
    set_sign_long(&diff, !get_sign_long(ld1));
  }

  int temp = 0;
  for (int i = 0; i < 192; i++) {
    int b1 = get_bit_long(ld1, i);
    int b2 = get_bit_long(ld2, i);
    int b3 = sub_bits(b1, b2, &temp);
    set_bit_long(&diff, i, b3);
  }
  copy_longdec(diff, result);
}

void mantissa_shift_left_long(long_dec ld, long_dec *result) {
  long_dec temp;
  copy_longdec(ld, &temp);
  for (int i = 191; i > 0; i--)
    set_bit_long(&temp, i, get_bit_long(temp, i - 1));
  set_bit_long(&temp, 0, 0);
  copy_longdec(temp, result);
}

void mul(long_dec ld1, long_dec ld2, long_dec *result) {
  long_dec sum = {0};

  for (int i = 0; i < 96; i++) {
    int b2 = get_bit_long(ld2, i);
    if (b2) add(sum, ld1, &sum);
    mantissa_shift_left_long(ld1, &ld1);
  }

  set_sign_long(&sum, abs((get_sign_long(ld1) - get_sign_long(ld2))));
  set_exp_long(&sum, get_exp_long(ld1) + get_exp_long(ld2));
  copy_longdec(sum, result);
}

void add_exp(long_dec value, long_dec *result) {
  long_dec temp, ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  mul(value, ten, &temp);
  set_exp_long(&temp, get_exp_long(value) + 1);
  copy_longdec(temp, result);
}

int mantissa_is_zero(long_dec ld1) {
  int flag = 1;
  for (int i = 0; i < 192; i++)
    if (get_bit_long(ld1, i)) {
      flag = 0;
      break;
    }
  return flag;
}

void div_int(long_dec ld1, long_dec ld2, long_dec *result) {
  long_dec quotient = {0}, diff = {0};

  set_sign_long(&diff, get_sign_long(ld2));
  set_exp_long(&diff, get_exp_long(ld2));

  for (int i = 191; i >= 0; i--) {
    mantissa_shift_left_long(diff, &diff);
    mantissa_shift_left_long(quotient, &quotient);
    set_bit_long(&diff, 0, get_bit_long(ld1, i));
    set_bit_long(&quotient, 0, mantissa_is_greater_or_equal(diff, ld2));
    if (mantissa_is_greater_or_equal(diff, ld2)) sub(diff, ld2, &diff);
  }

  set_sign_long(&quotient, abs((get_sign_long(ld1) - get_sign_long(ld2))));
  set_exp_long(&quotient, get_exp_long(ld1) - get_exp_long(ld2));

  if (mantissa_is_zero(ld2)) {
    set_exp_long(&quotient, 0);
    set_bit_long(&quotient, 96, 1);
  }
  copy_longdec(quotient, result);
}

void sub_exp(long_dec value, long_dec *result) {
  long_dec temp, ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  div_int(value, ten, &temp);
  set_exp_long(&temp, get_exp_long(value) - 1);
  copy_longdec(temp, result);
}

void mod(long_dec ld1, long_dec ld2, long_dec *result) {
  long_dec quotient = {0}, diff = {0};

  set_sign_long(&diff, get_sign_long(ld2));
  set_exp_long(&diff, get_exp_long(ld2));

  for (int i = 191; i >= 0; i--) {
    mantissa_shift_left_long(diff, &diff);
    mantissa_shift_left_long(quotient, &quotient);
    set_bit_long(&diff, 0, get_bit_long(ld1, i));
    set_bit_long(&quotient, 0, mantissa_is_greater_or_equal(diff, ld2));
    if (mantissa_is_greater_or_equal(diff, ld2)) sub(diff, ld2, &diff);
  }

  if (mantissa_is_zero(ld2)) {
    set_exp_long(&diff, 0);
    set_bit_long(&diff, 96, 1);
    diff.bits[2] = UINT32_MAX;
    diff.bits[1] = UINT32_MAX;
    diff.bits[0] = UINT32_MAX;
  }

  set_sign_long(&diff, get_sign_long(ld1));
  copy_longdec(diff, result);
}

void round_bank(long_dec value, long_dec *result) {
  long_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  long_dec one = {{1, 0, 0, 0, 0, 0}, 0, 0};
  long_dec temp, digit_0, digit_1;
  mod(value, ten, &digit_0);
  div_int(value, ten, &temp);
  mod(temp, ten, &digit_1);
  if ((digit_0.bits[0] == 5 && digit_1.bits[0] % 2) || digit_0.bits[0] > 5)
    add(temp, one, &temp);
  set_exp_long(&temp, get_exp_long(value) - 1);
  copy_longdec(temp, result);
}

void round_dec(long_dec value, long_dec *result) {
  long_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  long_dec one = {{1, 0, 0, 0, 0, 0}, 0, 0};
  long_dec temp, digit_0;
  mod(value, ten, &digit_0);
  div_int(value, ten, &temp);
  if (digit_0.bits[0] >= 5) add(temp, one, &temp);
  set_exp_long(&temp, get_exp_long(value) - 1);
  copy_longdec(temp, result);
}

void normalize_long(long_dec *ld1, long_dec *ld2) {
  long_dec temp,
      max_dec = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0, 0, 0}, 0, 0};
  int n = get_exp_long(*ld2) - get_exp_long(*ld1);
  if (n != 0) {
    long_dec *v = (n > 0 ? ld1 : ld2);
    int pow = get_exp_long(n > 0 ? *ld2 : *ld1);
    copy_longdec(*v, &temp);
    while (get_exp_long(*v) < pow && mantissa_is_less_or_equal(temp, max_dec)) {
      add_exp(temp, v);
      add_exp(temp, &temp);
    }
    n = get_exp_long(*ld2) - get_exp_long(*ld1);
    if (n != 0) {
      long_dec *v = (n > 0 ? ld2 : ld1);
      int pow = get_exp_long(n > 0 ? *ld1 : *ld2);
      copy_longdec(*v, &temp);
      while (get_exp_long(*v) > pow) {
        if (mantissa_is_greater_long(temp, max_dec))
          round_bank(temp, v);
        else
          round_dec(temp, v);
        sub_exp(temp, &temp);
      }
    }
  }
}

void longdec_to_dec(long_dec value, s21_decimal *result) {
  long_dec temp,
      max_dec = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0, 0, 0}, 0, 0};
  copy_longdec(value, &temp);
  while (mantissa_is_greater_long(value, max_dec)) {
    if (get_exp_long(temp) == 0) break;
    round_bank(temp, &value);
    sub_exp(temp, &temp);
  }
  copy_longdec(value, &temp);
  while (get_exp_long(value) > 28) {
    round_dec(temp, &value);
    sub_exp(temp, &temp);
  }
  copy_longdec(value, &temp);

  while (get_exp_long(value) < 0 && mantissa_is_less_or_equal(temp, max_dec)) {
    add_exp(temp, &value);
    add_exp(temp, &temp);
  }

  set_sign(result, get_sign_long(value));

  if (get_exp_long(value) < 0 ||
      (get_exp_long(value) == 0 && mantissa_is_greater_long(value, max_dec))) {
    set_exp(result, 0);
    set_bit(result, 96, 1);
    result->bits[2] = UINT32_MAX;
    result->bits[1] = UINT32_MAX;
    result->bits[0] = UINT32_MAX;
  } else {
    set_exp(result, get_exp_long(value));
    result->bits[2] = value.bits[2];
    result->bits[1] = value.bits[1];
    result->bits[0] = value.bits[0];
  }
}

void init_dec(int sign, int exp, unsigned int b2, unsigned int b1,
              unsigned int b0, s21_decimal *result) {
  result->bits[0] = b0;
  result->bits[1] = b1;
  result->bits[2] = b2;
  result->bits[3] = 0;
  set_sign(result, sign);
  set_exp(result, exp);
}

void div_dec(long_dec ld1, long_dec ld2, long_dec *result) {
  long_dec temp = {0}, diff = {0},
           max_dec = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0, 0, 0}, 0, 0};

  while (mantissa_is_less_or_equal(temp, max_dec)) {
    div_int(ld1, ld2, &temp);
    mod(ld1, ld2, &diff);
    if (mantissa_is_zero(diff)) break;
    add_exp(ld1, &ld1);
  }
  copy_longdec(temp, result);
}

int simple_div(s21_decimal d1, s21_decimal d2, s21_decimal *result) {
  s21_decimal value = {0};
  s21_decimal diff = {0};

  // init_dec(get_sign(d2), get_pow(d2), 0, 0, 0, &diff);

  for (int i = 95; i >= 0; i--) {
    mantissa_shift_left(&diff);
    set_bit(&diff, 0, get_bit(d1, i));
    set_bit(&value, i, !mantissa_is_greater(d2, diff));
    if (!mantissa_is_greater(d2, diff)) s21_sub(diff, d2, &diff);
  }
  set_sign(&value, abs(get_sign(d1) - get_sign(d2)));
  set_exp(&value, get_exp(d1) - get_exp(d2));

  copy_dec(result, value);

  return 0;
}

void mantissa_shift_left(s21_decimal *value) {
  s21_decimal temp;
  copy_dec(&temp, *value);
  for (int i = 96; i > 0; i--) set_bit(&temp, i, get_bit(temp, i - 1));
  set_bit(&temp, 0, 0);
  copy_dec(value, temp);
}

int mantissa_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = 96; i >= 0; i--)
    if (get_bit(value_1, i) != get_bit(value_2, i)) {
      res = get_bit(value_1, i);
      break;
    }
  return res;
}

int simple_fmod(s21_decimal d1, s21_decimal d2) {
  int mod = 0;
  s21_decimal diff = {0};
  s21_decimal value;
  for (int i = 95; i >= 0; i--) {
    mantissa_shift_left(&diff);
    set_bit(&diff, 0, get_bit(d1, i));
    set_bit(&value, i, !mantissa_is_greater(d2, diff));
    if (!mantissa_is_greater(d2, diff)) {
      s21_sub(diff, d2, &diff);
    }
  }
  mod = diff.bits[0];
  return mod;
}

// additional
int s21_get_bit(s21_decimal value, int index) {
  return (value.bits[index / 32] >> (index % 32)) & 1U;
}

void s21_set_bit(s21_decimal *value, int index, int bit_value) {
  if (bit_value) {
    (value->bits[index / 32] |= (1U << index % 32));
  } else {
    value->bits[index / 32] &= ~(1U << index % 32);
  }
}

int getpow(s21_decimal value_1) {
  int result = 0, temp;
  for (int i = 16; i < 24; ++i) {
    temp = s21_get_bit(value_1, i + 96);
    if (temp) {
      result += pow(2, i - 16);
    }
  }
  return result;
}

void nullValue(s21_decimal *value) {
  for (int j = 0; j < 4; ++j) {
    value->bits[j] = 0;
  }
}

void putpow(s21_decimal *value_1, int power) {
  s21_decimal temp;
  nullValue(&temp);
  temp.bits[0] = power;
  for (int i = 0; i < 8; i++) {
    s21_set_bit(value_1, i + 112, s21_get_bit(temp, i));
  }
}

void nullValueLong(long_dec *value) {
  for (int j = 0; j < 6; j++) {
    value->bits[j] = 0;
  }
}

int getsign(s21_decimal value_1) { return s21_get_bit(value_1, 127); }

int s21_get_bit_long(long_dec value, int index) {
  return (value.bits[index / 32] >> (index % 32)) & 1U;
}

void s21_set_bit_long(long_dec *value, int index,
                      int bit_value) {  // bit_value_ 1 или 0 - проверка!
  if (bit_value) {
    (value->bits[index / 32] |= (1U << index % 32));
  } else {
    value->bits[index / 32] &= ~(1U << index % 32);
  }
}

int decimalToLongDecimal(s21_decimal value, long_dec *result) {
  int resultFunc = 0, pow_value = 28 - getpow(value), part1_pow = pow_value / 2,
      part2_pow = pow_value - part1_pow, sign = getsign(value);
  long_dec intermediate;
  nullValueLong(&intermediate);
  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }
  result->bits[3] = 0;
  result->bits[4] = 0;
  result->bits[5] = 0;
  s21_set_bit_long(result, 191, sign);
  put_llintInLongDecimal(&intermediate, pow(10, part1_pow));
  mul_long(*result, intermediate, result);
  nullValueLong(&intermediate);
  put_llintInLongDecimal(&intermediate, pow(10, part2_pow));
  mul_long(*result, intermediate, result);
  return resultFunc;
}

int mul_long(long_dec value_1, long_dec value_2,
             long_dec *result) {  // умножение для сравнения без степеней
  int bit, resultCode = 0;
  long_dec intermediate;
  nullValueLong(&intermediate);
  nullValueLong(result);
  mulSign_long(value_1, value_2, result);
  for (int i = 0; i < 191 && resultCode == 0; i++) {
    bit = s21_get_bit_long(value_2, i);
    if (bit) {
      if (shiftLeft_long(value_1, i, &intermediate) == 0) {
        resultCode = sumLong(intermediate, *result, result);
        nullValueLong(&intermediate);
      }
    }
  }
  return resultCode;
}

int shiftLeft_long(
    long_dec value, int shiftValue,
    long_dec *shiftedValue) {  //сдвиг s21_decimal влево на shiftValue
  nullValueLong(shiftedValue);
  int bit, result = 0;
  for (int i = 190; i >= 0; i--) {
    bit = s21_get_bit_long(value, i);
    if (bit && (i + shiftValue) > 190) {
      result = 1;
      break;
    } else if ((i + shiftValue) < 191) {
      s21_set_bit_long(shiftedValue, i + shiftValue, bit);
    }
  }
  return result;
}

int sumLong(
    long_dec value_1, long_dec value_2,
    long_dec *value) {  //Эта функция нужна для работы функции умножения!
  int temp, next = 0, result = 0;
  for (int i = 0; i < 191; i++) {  // 191 ый бит под знак!
    temp = s21_get_bit_long(value_1, i) + s21_get_bit_long(value_2, i) + next;
    switch (temp) {
      case 3:
        s21_set_bit_long(value, i, 1);
        next = 1;
        break;

      case 2:
        s21_set_bit_long(value, i, 0);
        next = 1;
        break;

      case 1:
        s21_set_bit_long(value, i, 1);
        next = 0;
        break;

      default:
        s21_set_bit_long(value, i, 0);
        next = 0;
        break;
    }
    temp = 0;
  }
  if (next) {
    result = 1;
  }
  return result;
}

void put_llintInLongDecimal(long_dec *value, long long number) {
  nullValueLong(value);
  for (int i = 0; i < 64; i++) {
    s21_set_bit_long(value, i, (number >> i & 1U));
  }
  s21_set_bit_long(value, 191, (number >> 63 & 1U));  //знак плюс или минус
}

int getsign_long(long_dec value_1) { return s21_get_bit_long(value_1, 191); }

void mulSign_long(long_dec value_1, long_dec value_2, long_dec *result) {
  int sign_1 = getsign_long(value_1), sign_2 = getsign_long(value_2);
  if (sign_1 == sign_2) {
    s21_set_bit_long(result, 191, 0);
  } else {
    s21_set_bit_long(result, 191, 1);
  }
}

int s21_greater_long_without_sign(long_dec value_1, long_dec value_2) {
  int result = 2;  // 0 - больше, 1 - меньше, 2 - равны
  for (int i = 190; i >= 0 && result == 2; i--) {
    if (s21_get_bit_long(value_1, i) > s21_get_bit_long(value_2, i)) {
      result = 0;
    } else if (s21_get_bit_long(value_1, i) < s21_get_bit_long(value_2, i)) {
      result = 1;
    }
  }
  return result;
}

// void print_binary(int n) {
//     for (int i = 31; i >= 0; i--) {
//         if (n & (1 << i)) {
//             printf("1");
//         } else {
//             printf("0");
//         }
//     }
//     printf(" ");
// }

// void print_decimal_binary(s21_decimal d) {
//   print_binary(d.bits[3]);
//   print_binary(d.bits[2]);
//   print_binary(d.bits[1]);
//   print_binary(d.bits[0]);
// }

// void print_long_decimal_binary(long_dec ld) {
//   printf("%d ", ld.sign);
//   printf("%d ", ld.exp);
//   print_binary(ld.bits[5]);
//   print_binary(ld.bits[4]);
//   print_binary(ld.bits[3]);
//   print_binary(ld.bits[2]);
//   print_binary(ld.bits[1]);
//   print_binary(ld.bits[0]);
// }