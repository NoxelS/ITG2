# Vollautomatisches Makefile
# - Sucht nach allen .cpp Files und erzeugt.o Files daraus
# - Sucht nach dem main-File und erzeugt dann ein exec mit dessen Namen
# - Löscht alle .o Files

CC	= g++-10
CFLAGS	= -g -Wall -c -std=c++20
LDFLAGS	= -g -lm -lrt -lpthread
SRC	= $(wildcard src/*.cpp)
HDR	= $(wildcard src/*.h)
OBJ	= $(SRC:.cpp=.o)
EXE	= main #$(shell egrep -l ".* main\(.*\)" src/*.cpp | sed s/".cpp"/""/g | tail -n 1)

all: main
	rm -f */*.o
	rm -f */*.s
	rm -f */*.ii
	

main:	src/main.cpp
	g++-10 ./src/main.cpp -o main


clean:
	rm -f */*.o
	rm -f */*.s
	rm -f */*.ii
	rm -f $(EXE)
	rm -f ./$(EXE)
	rm -f test
	rm -f rpn