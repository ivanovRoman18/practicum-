clear:
	rm -rf *.o *.a *_test
	make -C ../linear_allocator clear || exit 1; \

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

linear_allocator/linear_allocator.a:
	make -C ../linear_allocator linear_allocator.a || exit 1; \

array_list.o: array_list.h array_list.c
	gcc -g -c array_list.c -o array_list.o

array_list.a: array_list.o
	ar rc array_list.a array_list.o

array_list_test.o: array_list_test.c
	gcc -g -c array_list_test.c -o array_list_test.o

array_list_test: array_list_test.o array_list.a linear_allocator/linear_allocator.a
	gcc -g -static -o array_list_test array_list_test.o array_list.a ../linear_allocator/linear_allocator.a -lm

test: array_list_test
	./array_list_test
