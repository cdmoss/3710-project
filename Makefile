CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lglut -lGLU -lGL
NAME=terry
SOURCES=$(NAME).cc
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(NAME)

all: init $(SOURCES) $(EXECUTABLE) clean

init:
	mkdir -p bin

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/$@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.d *.o 