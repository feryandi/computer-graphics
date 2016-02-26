#pragma once

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
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

#include "FrameBuffer.class.h"

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

		int wireRed;
		int wireGreen;
		int wireBlue;

		// Scanline		
		int nLine;
		int **oosMap;

		int fillRed;
		int fillGreen;
		int fillBlue;

		// Private Methods
		int *intdup(int const * src, size_t len);

		// Bresenham algorithm
		int iabs(int n);
		int F(int X, int Y, int Z);
		int G(int X, int Y);
		void bresenham(int, int, int, int, int, int, int, int, FrameBuffer*);

		// OOS Scanline algorithm
		void clearMap();
		int isCriticalPoint(int, int, int);
		int isIntersect(int, int);
		int isHorizontalLine(int);
		int xIntersect(int, int);
		int getMiddleX(int e);
		void fill(int, int, FrameBuffer*);

	public:
		Polygon(int cx, int cy, int*, int len);
		~Polygon();

		int getX();
		int getY();
		void setPosition(int, int);

		int getCX();
		int getCY();
		void setCenter(int, int);

		void setMultiplication(float);		
		float getMultiplication();

		void setDegree(float);
		float getDegree();

		void setWireframe(int*, int);

		void setWireColor(int r, int g, int b);
		void setFillColor(int, int, int);

		void draw(FrameBuffer *fb);

		class intersection {
		public:
			int edge;
			int x;
			int type;

			intersection(int _e, int _x, int _type): edge(_e), x(_x), type(_type) {
			}

			friend bool operator> (intersection&, intersection&); 
			friend bool operator< (intersection&, intersection&); 
        };

};

inline bool operator> (Polygon::intersection &i1, Polygon::intersection &i2) {
    return i1.x > i2.x;
}

inline bool operator< (Polygon::intersection &i1, Polygon::intersection &i2) {
    return i1.x < i2.x;
}

#endif
