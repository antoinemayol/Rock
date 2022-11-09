CC = gcc
CPPFLAGS =
CFLAGS = -Wall  -Wextra `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

all: display grayscale

SRC = $(shell find -name "*.c")
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

main: rotation.o main.o
	gcc -o main $(CFLAGS) $^ $(LDLIBS)

disp: display.o
	gcc -o disp $(CFLAGS) $^ $(LDLIBS)


.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} main
	${RM} disp

# END
