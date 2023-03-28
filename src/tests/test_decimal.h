#ifndef TEST_DECIMAL_H
#define TEST_DECIMAL_H

#include <check.h>

#include "s21_additional.h"
#include "s21_decimal.h"

Suite *suite_s21_compare();
Suite *suite_s21_arithmetic();
Suite *suite_s21_other();
Suite *suite_s21_convertors();

Suite *suite_mul(void);
Suite *suite_is_greater(void);
Suite *suite_is_less(void);

Suite *suite_from_float_to_decimal(void);

#endif  // TEST_DECIMAL_H
