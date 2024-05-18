CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard s21_*.c)
HEADER = $(wildcard s21_*.h)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
TESTS_SOURCE = tests.c
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread
endif
ifeq ($(UNAME_S), Darwin)
	ADD_LIB = -lcheck -lm -lpthread
endif

all: clean build

build: s21_matrix.a

s21_matrix.a: ${SOURCE}
	${CC} ${CFLAGS} -c ${SOURCE}
	ar rc $@ $(OBJECTS)
	ranlib $@

test: ${TESTS_SOURCE} clang
	${CC} -g ${SOURCE} ${TESTS_SOURCE} $(ADD_LIB) -o tests
	valgrind -s --leak-check=full --show-leak-kinds=all ./tests

lcov:
	ifeq ("", "$(shell PATH=$(PATH) which lcov)")
		$(error Need to install lcov)
	endif

gcov_report:
	${CC} -g --coverage ${SOURCE} ${TESTS_SOURCE} $(ADD_LIB) -o tests
	./tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	rm -rfd *.gcda *.gcno *.out tests

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
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

.PHONY: all build clean lcov clang gcov_report test