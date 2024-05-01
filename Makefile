CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard s21_*.c)
HEADER = $(wildcard s21_*.h)
TESTS_SOURCE = tests.c
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)

endif
ifeq ($(UNAME_S), Darwin)

endif

all:

test: clang

lcov:

gcov_report:

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm -rf .clang-format

clean:
	rm -rf *.o && rm -rf *.gcno
	rm -rf *.a && rm -rf *.gcda
	rm -rf *.info 
	rm -rf *.gcov
	rm -rf ./test
	rm -rf ./gcov_report
	rm -rf ./report/
	rm -rf s21_test
	rm -rf *.out
	rm -rf .clang-format

.PHONY: all clean lcov clang gcov_report test