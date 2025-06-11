clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

integral.o: integral.h integral.c
	gcc -g -c integral.c -o integral.o

integral.a: integral.o
	ar rc integral.a integral.o

integral_test.o: integral_test.c
	gcc -g -c integral_test.c -o integral_test.o

integral_test: integral_test.o integral.a
	gcc -g -static -o integral_test integral_test.o integral.a -lm

test: integral_test
	./integral_test
