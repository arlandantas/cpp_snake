# CC = g++
# CFLAGS = -wall -g

# TARGET: cpp_snake

all: main

main: main.o Board2D.o
	g++ -o cpp_snake main.o Board2D.o
	# $(CC) $(CFLAGS) -o cpp_snake main.o Board2D.o

main.o: main.cpp headers/Board2D.h
	g++ -o main.o main.cpp -c -W -Wall
	# $(CC) $(CFLAGS) -c main.cpp

Board2D.o: Board2D.cpp headers/Board2D.h
	g++ -o Board2D.o Board2D.cpp -c -W -Wall

clean:
	rm $(TARGET)
