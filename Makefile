SRCS = $(wildcard *_test.c)
PRGS = $(patsubst %.c, %, $(SRCS))
LIBS = $(patsubst %_test.c, %.a, $(SRCS))

test: $(PRGS)
	for test in $(PRGS); do \
		echo "Running $$test"; \
		valgrind --leak-check=full --errors-for-leak-kinds=all --undef-value-errors=no --error-exitcode=1 \
		         ./$$test || exit 1; \
	done;

clear: 
	rm -rf *.o *.a *_test

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

%.o: %.c %.h
	gcc -g -c $< -o $@

%.a: %.o
	ar rc $@ $^

%_test.o: %_test.c
	gcc -g -c $^ -o $@

%_test: %_test.o $(LIBS)
	gcc -g -static -o $@ $^ -lm