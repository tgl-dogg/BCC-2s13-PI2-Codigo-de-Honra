CC=gcc -std=c99
CFLAGS= −W −Wall
EXEC=game
#SRC:= $(wildcard *.c)
SRC:= $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c)
#SRC:= $(wildcard **/*.c)
OBJ= $(SRC:.c=.o)
LIBS=-lallegro -lallegro_image -lallegro_font -lallegro_ttf

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	rm -rf $(OBJ)