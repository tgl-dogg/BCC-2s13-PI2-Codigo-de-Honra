CC=gcc -std=c99
CFLAGS= −W −Wall
EXEC=game
#SRC:= $(wildcard *.c)
SRC:= $(wildcard *.c) $(wildcard */*.c)
OBJ= $(SRC:.c=.o)
LIBS=-lallegro -lallegro_image

all: $(EXEC) clean

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	rm -rf $(OBJ)