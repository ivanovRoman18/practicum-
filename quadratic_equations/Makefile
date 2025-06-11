clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

quadratic_equations.o: quadratic_equations.h quadratic_equations.c
	gcc -g -c quadratic_equations.c -o quadratic_equations.o

quadratic_equations.a: quadratic_equations.o
	ar rc quadratic_equations.a quadratic_equations.o

quadratic_equations_test.o: quadratic_equations_test.c
	gcc -g -c quadratic_equations_test.c -o quadratic_equations_test.o

quadratic_equations_test: quadratic_equations_test.o quadratic_equations.a
	gcc -g -static -o quadratic_equations_test quadratic_equations_test.o quadratic_equations.a -lm

test: quadratic_equations_test
	./quadratic_equations_test
