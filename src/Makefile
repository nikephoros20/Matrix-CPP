GCC=gcc
SRC=S21Matrix.cc
OBJ=S21Matrix.o
CFLAGS=--std=c++17 -lstdc++ -Wall -Werror -Wextra
TESTFLAGS=-lgtest -lgcov
GCOVFLAGS=--coverage
HTML=lcov -t test -o rep.info -c -d ./ --exclude *14/*
OS = $(shell uname)

ifeq ($(OS),Darwin)
	OPEN_CMD = open
else
	CFLAGS += -lm 
	OPEN_CMD = xdg-open
endif

all: clean gcov_report

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM

test: s21_matrix_oop.a
	$(GCC) -g test.cc s21_matrix_oop.a $(CFLAGS) $(TESTFLAGS) -o test
	./test

s21_matrix_oop.a: clean
	$(GCC) $(GCOVFLAGS) -c $(SRC)
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a

gcov_report: test
	$(HTML)
	genhtml -o report rep.info
	$(OPEN_CMD) report/index.html

