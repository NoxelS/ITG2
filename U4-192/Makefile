CC = g++
CFLAGS = -w

all: main.o
	$(CC) $(CFLAGS) -o main main.o

clean:
	rm -f *.o main
	rm -f src/*.o
	rm -f tests/*.o

clean-output:
	rm -f */*.o