.PHONY: all clean
CC = gcc
CFLAGS = -g -Wall
Sources := $(filter %.c, $(shell ls))#main.o job.o
OBJ := $(Sources:.c=.o)

test: $(OBJ)
	$(CC) $^ -o $@
clean:
	rm -f $(OBJ)
