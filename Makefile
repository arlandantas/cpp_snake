CC = g++
TARGET = cpp_snake
SRC_PATH=src/
HEADER_PATH=$(SRC_PATH)/headers/
BUILD_PATH=.build/
PATH_FLAGS = -B $(SRC_PATH)
CFLAGS = -g $(PATH_FLAGS)
# -Wall

all: main

main: create-build clean main.o Board2D.o
	$(CC) -o $(TARGET) $(BUILD_PATH)main.o $(BUILD_PATH)Board2D.o

main.o: $(SRC_PATH)main.cpp $(HEADER_PATH)Board2D.h
	$(CC) $(CFLAGS) -o $(BUILD_PATH)main.o -c $(SRC_PATH)main.cpp

Board2D.o: $(SRC_PATH)Board2D.cpp $(HEADER_PATH)Board2D.h
	$(CC) $(CFLAGS) -o $(BUILD_PATH)Board2D.o -c $(SRC_PATH)Board2D.cpp

clean:
	rm -rf *.o *~ $(TARGET) $(BUILD_PATH)*

create-build:
	if [ ! -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
