#!/bin/bash

docker build . -t s21_decimal_test:1.0 -f ./tests/scripts/Dockerfile
docker run s21_decimal_test:1.0
