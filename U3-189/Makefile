# Vollautomatisches Makefile
# - Sucht nach allen .cpp Files und erzeugt.o Files daraus
# - Sucht nach dem main-File und erzeugt dann ein exec mit dessen Namen
# - Löscht alle .o Files

CC	= g++
CFLAGS	= -g -Wall -c -std=c++11
LDFLAGS	= -g -lm -lrt
SRC	= $(wildcard *.cpp)
HDR	= $(wildcard *.h)
OBJ	= $(SRC:.cpp=.o)
EXE	= $(shell egrep -l ".* main\(.*\)" *.cpp | sed s/".cpp"/""/g | tail -n 1)

all:	$(EXE)
	
$(EXE):	$(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	rm *.o
			
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
