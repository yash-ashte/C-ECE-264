# VARIABLES
ASG_NICKNAME=Hw13
CC=gcc
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
BASE_NAME=json
SRC_C=$(BASE_NAME).c
SRC_H=$(BASE_NAME).h clog.h miniunit.h
EXECUTABLE=test_$(BASE_NAME)
EXECUTABLE_GCOV=$(EXECUTABLE)_gcov
TEST_C=$(EXECUTABLE).c
SUBMIT_FILES=$(SRC_C) $(TEST_C) $(SRC_H) Makefile
SHELL=/bin/bash


# RULES

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H) 
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

submit: $(SUBMIT_FILES)
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

pretest: submit
	264test $(ASG_NICKNAME)

clean:
	rm -f $(EXECUTABLE_GCOV) $(EXECUTABLE) *.c.gcov *.gcda *gcno

valgrind: $(EXECUTABLE)
	valgrind $(EXECUTABLE)

coverage: $(TEST_C) $(SRC_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE_GCOV)
	gcov -f $(SRC_C)

.PHONY: submit test pretest clean coverage
