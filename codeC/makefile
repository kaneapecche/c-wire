	CC = gcc
	CFLAGS = -Wall -g -std=c99
TARGET = programme
SRC = main.c AVL.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c AVL.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
	
