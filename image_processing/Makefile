# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -fsanitize=address -Wextra `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

all: main

SRC = $(shell find -name "*.c")
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

main: $(OBJ)
	gcc -o main $(CFLAGS) $^ $(LDLIBS)

demo:$(OBJ)
	gcc -o demo $(CFLAGS) $^ $(LDLIBS)

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} main

# END
