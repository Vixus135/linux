CC = gcc
CFLAGS = -c
TARGET = proizvodstvo

$(TARGET): funcs.c main.c
	$(CC) main.c funcs.c -o $(TARGET) -lpthread
clean:
	rm -f *.o $(TARGET)

