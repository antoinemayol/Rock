# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -g -Wextra -fsanitize=address
LDFLAGS =
LDLIBS = -lm 
SUBDIRS = image_processing detection

SRC = main.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: subdirs main

main: $(OBJ)
	gcc -o main $(CFLAGS) $^ $(LDLIBS)


subdirs:$(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} main
# END
