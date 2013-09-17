CC=gcc -std=c99
CFLAGS=−W −Wall
EXEC=game
SRC:= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS=-lallegro -lallegro_image

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(wildcard *.o)