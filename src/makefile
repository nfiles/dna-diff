CC = g++
BIN = ../bin/dna-diff.exe

DEBUG = -g -Wall
# ref: http://stackoverflow.com/a/4703059
FLAGS = -static-libgcc -static-libstdc++
RELEASE = -O3

OBJECTS = result.h reporter.o blast-reporter.o column-reporter.o \
		  engine.o main.o
NOHEADER = main.o

# included files
REPORTER = reporter.h reporter.cpp
BLASTREPORTER = blast-reporter.h blast-reporter.cpp
COLUMNREPORTER = column-reporter.h column-reporter.cpp
RESULT = result.h
ENGINE = engine.h engine.cpp

FILES = $(REPORTER) $(BLASTREPORTER) $(COLUMNREPORTER) \
		$(RESULT) $(ENGINE) main.cpp

TEMP = *.o *.gch *.stackdump

build : $(OBJECTS)
	$(CC) $(FLAGS) $^ -o $(BIN)

main.o : main.cpp
$(NOHEADER) :
	$(CC) -c $(DEBUG) $^

%.o : %.h %.cpp
	$(CC) -c $(DEBUG) $^

release : $(FILES)
	$(CC) $(RELEASE) $^ -o $(BIN)

clean :
	rm -f $(TEMP) $(BIN)

rebuild : clean build
