# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -Wextra `pkg-config --cflags sdl2 SDL2_image gtk+-3.0` -rdynamic 
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image gtk+-3.0`

TARGET = interface
BUILD := build

SRC = $(shell find ./ -name "*.c" ! -name "main.c")
OBJ = $(SRC:%.c=$(BUILD)/%.o)
DEP = $(SRC:%.c=$(BUILD)/%.d)

all: init main clear

clear:
	find . -type d -empty -delete

init:
	$(shell mkdir -p $(BUILD))
	$(shell mkdir -p $(SRC:%.c=$(BUILD)/%))

main: $(OBJ)
	gcc -o $@ $(CFLAGS) $^ $(LDLFLAGS) $(LDLIBS)

$(BUILD)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDLFLAGS) $(CPPFLAGS) $(LDLIBS)

.PHONY: all $(SUBDIRS)

clean:
	$(RM) -f $(EXE) $(OBJ)
	rm -rf $(BUILD)
	${RM} ${OBJ} ${DEP} main
	${RM} grille.bmp grille_g.bmp
	clear

# END
