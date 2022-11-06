CC = g++
TARGET = cpp_snake
SRC_PATH=src/
HEADER_PATH=$(SRC_PATH)/headers/
BUILD_PATH=.build/
PATH_FLAGS = -B $(SRC_PATH)
CFLAGS = -g $(PATH_FLAGS) -Wall

all: main

main: create-build clean Board2D.o SnakeGame.o main.o
	$(CC) $(BUILD_PATH)Board2D.o $(BUILD_PATH)SnakeGame.o $(BUILD_PATH)main.o -o $(TARGET)

main.o: $(SRC_PATH)main.cpp $(HEADER_PATH)Board2D.h
	$(CC) $(CFLAGS) -o $(BUILD_PATH)main.o -c $(SRC_PATH)main.cpp

Board2D.o: $(SRC_PATH)Board2D.cpp $(HEADER_PATH)Board2D.h
	$(CC) $(CFLAGS) -o $(BUILD_PATH)Board2D.o -c $(SRC_PATH)Board2D.cpp

SnakeGame.o: $(SRC_PATH)SnakeGame.cpp $(HEADER_PATH)Board2D.h $(HEADER_PATH)SnakeGame.h
	$(CC) $(CFLAGS) -o $(BUILD_PATH)SnakeGame.o -c $(SRC_PATH)SnakeGame.cpp

clean:
	rm -rf *.o *~ $(TARGET) $(BUILD_PATH)*

create-build:
	if [ ! -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
