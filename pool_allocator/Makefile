clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

pool_allocator.o: pool_allocator.h pool_allocator.c
	gcc -g -c pool_allocator.c -o pool_allocator.o

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

pool_allocator_test.o: pool_allocator_test.c
	gcc -g -c pool_allocator_test.c -o pool_allocator_test.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -static -o pool_allocator_test pool_allocator_test.o pool_allocator.a -lm

test: pool_allocator_test
	./pool_allocator_test
