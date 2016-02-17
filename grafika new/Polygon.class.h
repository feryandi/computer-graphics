#ifndef Polygon_Class_H
#define Polygon_Class_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265


class Polygon {
	private:
		// Posisi
		int x, y;	// Kiri Atas
		int cx, cy;	// Titik Tengah

		// Multiplication
		float k;

		// Rotation
		float d;

		// Wireframe
		int *wireframe;
		int len;

		// Bitmap
		int width;
		int height;
		int *bitmap;

		// Private Methods
		int *intdup(int const * src, size_t len);

		int iabs(int n);
		int F(int X, int Y, int Z);
		int G(int X, int Y);
		void bresenham(int, int, int, int, int*);

		void generateBitmap(int, int);

	public:
		Polygon(int cx, int cy, int*, int len);
		~Polygon();

		int getX();
		int getY();
		void setPosition(int, int);

		int getCX();
		int getCY();
		void setCenter(int, int);

		int getWidth();
		int getHeight();
		void setWireframe(int*, int);

		int* getBitmap();

		void setMultiplication(float);		
		float getMultiplication();

		void setDegree(float);
};

#endif
