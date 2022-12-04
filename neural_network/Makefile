# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -lm
LDFLAGS =
LDLIBS =

#all: mtest ntest ftest
	#${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

SRC = 	math_tool.c save_and_load.c neronXOR.c ../image_processing/processing_final.c ../image_processing/display.c ../image_processing/grayscale.c ../image_processing/image.c ../image_processing/otsu.c ../image_processing/blur.c


OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

nerons: neronXOR.o save_and_load.o math_tool.o ../image_processing/processing_final.o ../image_processing/display.o ../image_processing/image.o ../image_processing/otsu.o ../image_processing/blur.o
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} nerons
# END
