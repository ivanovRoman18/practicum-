SUBDIRS := $(shell find . -mindepth 1 -maxdepth 2 -type d -exec test -e '{}/Makefile' \; -print)

all: build

build:
	for dir in $(SUBDIRS); do \
		make -C $$dir || exit 1; \
	done

test:
	for dir in $(SUBDIRS); do \
		make -C $$dir test || exit 1; \
	done

clear:
	for dir in $(SUBDIRS); do \
		make -C $$dir clear; \
	done

fmt:
	for dir in $(SUBDIRS); do \
		make -C $$dir fmt; \
	done

check_fmt:
	for dir in $(SUBDIRS); do \
		make -C $$dir check_fmt; \
	done