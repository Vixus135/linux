CC = gcc
CFLAGS = -c
TARGET = proizPotrib

$(TARGET): funcs.c main.c
	$(CC) main.c funcs.c -o $(TARGET) -lpthread

clean:
	rm -f *.o $(TARGET)

