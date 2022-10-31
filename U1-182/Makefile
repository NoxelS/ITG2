CC = g++
CFLAGS = -w

demo: src/demo.o src/complex.o
	$(CC) $(CFLAGS) -o demo src/demo.o src/complex.o

unit_tests: tests/complex_test.o src/complex.o
	$(CC) $(CFLAGS) -o unit_tests tests/complex_test.o src/complex.o

clean:
	rm -f *.o demo unit_tests
	rm -f src/*.o
	rm -f tests/*.o