# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =

SRC = components_connexes.c test.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

test: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} test

# END
