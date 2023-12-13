CC=g++
TARGET=run
CFLAGS= -g
OBJS=test.o
# CFLAGS=-Wall -Wextra -Werror -std=c++11 -pthread -lrt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_template.o: SharedMemoryManager.hpp test.cpp
	$(CC) $(CFLAGS) -c test.cpp
