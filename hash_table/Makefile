clear:
	rm -rf *.o *.a *_test
	make -C ../pool_allocator clear || exit 1

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

pool_allocator/pool_allocator.a:
	make -C ../pool_allocator pool_allocator.a || exit 1

hash_table.o: hash_table.h hash_table.c
	gcc -g -c hash_table.c -o hash_table.o

hash_table.a: hash_table.o
	ar rc hash_table.a hash_table.o

hash_table_test.o: hash_table_test.c
	gcc -g -c hash_table_test.c -o hash_table_test.o

hash_table_test: hash_table_test.o hash_table.a pool_allocator/pool_allocator.a
	gcc -g -static -o hash_table_test hash_table_test.o hash_table.a ../pool_allocator/pool_allocator.a -lm

test: hash_table_test
	./hash_table_test
