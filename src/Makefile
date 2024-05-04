TARGETS=backend/*.c
CFLAGS=-std=c11 -Wall -Werror -Wextra 
TESTS=test/*.c
FLAG_TEST=-lcheck
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
VALGRIND = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
ifeq ($(shell uname), Linux)
	FLAG_TEST +=-lsubunit -lm
endif

all: clean 3d_viewer.a gcov_report

3d_viewer.a:$(OBJS)
	gcc $(CFLAGS) -c $(TARGETS)
	ar -rc 3d_viewer.a *.o
	ranlib 3d_viewer.a
	rm -rf *.o

install:
	mkdir build
	cd build && qmake ../3D_Viewer && make

uninstall:
	rm -rf build/

dist:
	tar -czf 3d_viewer.install.tar.gz ./* backend test 3D_Viewer

clean:
	rm -rf doxygen/
	rm -rf build/
	rm -rf *.gcno *.gcda testr 3d_viewer.a gcov_report report greport a.out *.txt *.dSYM *.info *.tar.gz
	
tests: 3d_viewer.a
	gcc --coverage $(CFLAGS) $(TESTS) 3d_viewer.a $(FLAG_TEST) -o testr -g
	./testr

gcov_report:
	gcc --coverage $(TARGETS) $(TESTS) $(FLAG_TEST) -o greport
	./greport
	lcov -t "test" -o 3d_viewer.info -c -d .
	genhtml -o ./report 3d_viewer.info
	open ./report/index.html

dvi:
	doxygen doxyfile
	open ./doxygen/html/index.html

style:
	clang-format -n --style=google backend/*.c backend/3d_viewer.h test/*.c test/*.h

html:
	open instruction.html

