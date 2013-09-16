CC = gcc
CFLAGS = −W −Wall
SRC = $(wildcard ∗.c)
OBJ = $(SRC:.c=.o)
LIBS = -lallegro -lallegro_image

all : exemplo

exemplo : $ (OBJ)
	$(CC) −o $@ $^ $(LIBS)

%.o : %.c
	$(CC) −o $@ −c $< $(CFLAGS)

.PHONY: clean

clean:
	rm −r f ∗.o
