# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -Wextra -fsanitize=address
LDFLAGS =
LDLIBS = -lm 


SRC = $(shell find -name "*.c")
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: main

main: $(OBJ)
	gcc -o main $(CFLAGS) $^ $(LDLIBS)

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} main

# END
