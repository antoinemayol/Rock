# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -fsanitize=address
LDFLAGS =
LDLIBS =

#all: mtest ntest ftest
	#${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

SRC = testMath.c testNeural.c math_tool.c Neuronal_link.c testNodes.c nerons.c main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all:  math_tool.o testNeural.o Neuronal_link.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

mtest: testMath.o math_tool.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

ntest: testNeural.o Neuronal_link.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

ftest: testNodes.o nerons.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

main: main.o math_tool.o Neuronal_link.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} mtest
	${RM} ntest
	${RM} ftest
	${RM} main
	${RM} all

# END
