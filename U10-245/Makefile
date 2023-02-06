# Vollautomatisches Makefile
# - Sucht nach allen .cpp Files und erzeugt.o Files daraus
# - Sucht nach dem main-File und erzeugt dann ein exec mit dessen Namen
# - Löscht alle .o Files

CC	= g++-10
CFLAGS	= -g -Wall -c -std=c++20 -fconcepts
LDFLAGS	= -g -lm -lrt -lpthread
SRC	= $(wildcard src/*.cpp)
SRC_NO_MAIN = $(shell egrep -L ".* main\(.*\)" src/*.cpp)
HDR	= $(wildcard src/*.h)
TESTS = $(wildcard tests/*.test.cpp)
TESTS_OBJ = $(TESTS:.cpp=.o)
OBJ	= $(SRC:.cpp=.o)
OBJ_NO_MAIN = $(SRC_NO_MAIN:.cpp=.o)
EXE	= main #$(shell egrep -l ".* main\(.*\)" src/*.cpp | sed s/".cpp"/""/g | tail -n 1)

all:	$(EXE)
	rm -f */*.o
	rm -f */*.s
	rm -f */*.ii
	
$(EXE):	$(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $@

test:	$(OBJ_NO_MAIN)	$(TESTS_OBJ)
	$(CC) $(OBJ_NO_MAIN) $(TESTS_OBJ) $(LDFLAGS) -o test
	./test --verbose
	rm -f */*.o
	rm -f */*.s
	rm -f */*.ii

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f */*.o
	rm -f */*.s
	rm -f */*.ii
	rm -f $(EXE)
	rm -f ./$(EXE)
	rm -f test