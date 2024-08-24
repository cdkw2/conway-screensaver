CC = gcc
CFLAGS = -Wall -Wextra -pedantic -D_GNU_SOURCE -std=gnu99
LDFLAGS = -lncurses -lm

SRC = conway.c
OBJ = $(SRC:.c=.o)
EXEC = conway

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
