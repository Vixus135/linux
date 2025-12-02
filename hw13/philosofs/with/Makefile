CC = gcc
CFLAGS = -c
TARGET = philo

$(TARGET): funcs.o main.o
	$(CC) main.o funcs.o -o $(TARGET) -lpthread

funcs.o: funcs.c
	$(CC) $(CFLAGS) funcs.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -f *.o $(TARGET)


