# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -Wextra `pkg-config --cflags sdl2 SDL2_image` -fsanitize=address -g
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

SUBDIRS = image_processing detection interface
MAKECMDGOALS = all

TARGET = main.c
SRC = $(shell find ./image_processing -name "*.c" ! -name "test.c" ! -name "demo.c")  $(shell find ./detection -name "*.c" ! -name "test.c" ! -name "demo.c")
OBJ = $(patsubst %.c, %.o, $(SRC))
EXE = ${TARGET:.c=}


all:$(SUBDIRS)
	gcc -o $(EXE) $(CFLAGS) $(TARGET) $(OBJ) $(LDLIBS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


.PHONY: all $(SUBDIRS)

clean:
	$(RM) -f $(EXE) $(OBJ)
# END
