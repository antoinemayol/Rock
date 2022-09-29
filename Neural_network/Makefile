# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS =

all: testM testN

SRC = testMath.c testNeural.c math_tool.c Neuronal_link.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

mtest: testMath.o math_tool.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

ntest: testNeural.o Neuronal_link.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@


-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} mtest
	${RM} ntest

# END
