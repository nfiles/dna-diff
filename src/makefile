CC = g++
BIN = ../bin/dna-diff.exe

DEBUG = -g -Wall
RELEASE = -O3

OBJECTS = dna-diff.o main.o
NOHEADER = main.o
FILES = dna-diff.cpp dna-diff.h main.cpp
TEMP = *.o *.gch *.stackdump

build : $(OBJECTS)
	$(CC) $^ -o $(BIN)

main.o : main.cpp
$(NOHEADER) :
	$(CC) -c $(DEBUG) $^

%.o : %.cpp %.h
	$(CC) -c $(DEBUG) $^

release : $(FILES)
	$(CC) $(RELEASE) $^ -o $(BIN)

clean :
	rm -f $(TEMP) $(BIN)

rebuild : clean build
