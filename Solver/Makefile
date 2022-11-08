# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -fsanitize=address
LDFLAGS =
LDLIBS =

#all: mtest ntest ftest
	#${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

SRC = parser.c solver.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}



main: parser.o solver.o  
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
