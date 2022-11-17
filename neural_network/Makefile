# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -lm
LDFLAGS =
LDLIBS =

#all: mtest ntest ftest
	#${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

SRC = 	math_tool.c save_and_load.c neronXOR.c

OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

nerons: neronXOR.o save_and_load.o math_tool.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} nerons
# END
