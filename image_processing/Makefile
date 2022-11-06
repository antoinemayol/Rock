# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -Wextra `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

all: display grayscale

SRC = display.c grayscale.c blur.c image.c main.c 
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

main: main.o display.o blur.o grayscale.o image.o

#display: display.o
#grayscale: grayscale.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} main

# END
