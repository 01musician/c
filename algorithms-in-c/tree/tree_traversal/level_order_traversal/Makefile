# compiler
CC = gcc
# flags
CFLAGS = -Wall -g
# general dependencies
DEPS = item.h list.h queue.h
# object files
OBJ = main.o item.o list.o queue.o
# main file name
TARGET = main
# out file name
OUT = level_order_traversal 
# standard
STD = -std=c99


all : $(TARGET) 

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(STD) -o $(OUT) $(OBJ) -lm

$(OBJ): $(DEPS)

.PHONY : clean
clean:
	rm -rf $(wildcard *.o) $(wildcard *~)
