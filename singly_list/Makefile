clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

singly_list.o: singly_list.h singly_list.c
	gcc -g -c singly_list.c -o singly_list.o

singly_list.a: singly_list.o
	ar rc singly_list.a singly_list.o

singly_list_test.o: singly_list_test.c
	gcc -g -c singly_list_test.c -o singly_list_test.o

singly_list_test: singly_list_test.o singly_list.a
	gcc -g -static -o singly_list_test singly_list_test.o singly_list.a -lm

test: singly_list_test
	./singly_list_test
