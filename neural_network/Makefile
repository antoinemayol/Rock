# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -lm `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

#all: mtest ntest ftest
	#${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

SRC = save_and_load.c neronXOR.c


OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

nerons: neronXOR.o save_and_load.o
	${CC} -o $@ ${CFLAGS} $^ $(LDLIBS)

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} nerons
# END
