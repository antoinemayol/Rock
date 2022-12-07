# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra 
LDFLAGS =
LDLIBS =

#all: mtest ntest ftest
	#${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

SRC = parser.c solver.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}



all: 
	${CC} -c ${CFLAGS} ${SRC}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}

# END
