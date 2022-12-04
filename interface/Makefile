# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wextra `pkg-config --cflags sdl2 SDL2_image` -Wall -rdynamic
LDLIBS = `pkg-config --libs gtk+-3.0` -lm `pkg-config --libs sdl2 SDL2_image`



EXE = interface display
OBJ = ${all:.c=.o}



all: interface

$(foreach f, $(EXE), $(eval *(f):))


display: display.o
	gcc -o disp $(CFLAGS) $^ $(LDLIBS)

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} ${OBJ}


# END
