# Sets default compiler
CC = g++

# Sets flags
CFLAGS = -Wall -Wextra -pedantic
CVERSION = -std=c++17

# Main
all: clean test0 test1 test2 test3 nGram

test0: test0.cpp
	# Compiles Test 0
	$(CC) $(CVERSION) $(CFLAGS) -o tester0.o test0.cpp

test1: test1.cpp
	# Compiles Test 1
	$(CC) $(CVERSION) $(CFLAGS) -o test1.o test1.cpp

test2: test2.cpp
	# Compiles Test 2
	$(CC) $(CVERSION) $(CFLAGS) -o test2.o test2.cpp

test3: test3.cpp
	# Compiles Test 3
	$(CC) $(CVERSION) $(CFLAGS) -o test3.o test3.cpp

nGram: nGram.cpp
	# Compiles nGram
	$(CC) $(CVERSION) $(CFLAGS) -o nGram.o nGram.cpp

clean:
	# Deletes binary files
	-rm $(objects) *.o