# Compiler to use
#CC=g++-4.9
CC=g++
CFLAGS=-c -Wall

all: main.o bezier.o frame_buffer.o point.o
	$(CC) main.o bezier.o frame_buffer.o point.o -o bezier_main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

bezier.o: bezier.cpp
	$(CC) $(CFLAGS) bezier.cpp

frame_buffer.o: frame_buffer.cpp
	$(CC) $(CFLAGS) frame_buffer.cpp

point.o: point.cpp
	$(CC) $(CFLAGS) point.cpp

clean:
	rm -f *.gch *.o bezier_main
