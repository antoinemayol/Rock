# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -Wextra 
LDFLAGS =
LDLIBS = -lm 


SRC = $(shell find -name "*.c")
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: test

test: $(OBJ)
	gcc -c $(CFLAGS) $^ $(LDLIBS)

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} main

# END
