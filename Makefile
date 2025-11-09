# Basic Makefile for test.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Target executable
TARGET = test

# Default rule
all: $(TARGET)

# How to build the target
$(TARGET): test.o
	$(CC) $(CFLAGS) -o $(TARGET) test.o

# How to build the object file
test.o: test.c
	$(CC) $(CFLAGS) -c test.c

# Clean up build files
clean:
	rm -f $(TARGET) *.o
