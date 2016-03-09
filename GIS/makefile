# Compiler to use
#CC=g++.4.9
CC=g++
CFLAGS=-c -Wall

all: main.o bezier_curve.o frame_buffer.o point.o input.o text.o polygon.o
	$(CC) main.o bezier_curve.o frame_buffer.o point.o input.o layer.o text.o polygon.o -o gis_itb

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

bezier_curve.o: bezier_curve.cpp
	$(CC) $(CFLAGS) bezier_curve.cpp

frame_buffer.o: frame_buffer.cpp
	$(CC) $(CFLAGS) frame_buffer.cpp

point.o: point.cpp
	$(CC) $(CFLAGS) point.cpp

input.o: input.cpp
	$(CC) $(CFLAGS) input.cpp

layer.o: layer.cpp
	$(CC) $(CFLAGS) layer.cpp


text.o: text.cpp
	$(CC) $(CFLAGS) text.cpp

polygon.o: polygon.cpp
	$(CC) $(CFLAGS) polygon.cpp

clean:
	rm -f *.gch *.o bezier_main
