#pragma once

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

#define PI 3.14159265


class Polygon {
	private:
		// Posisi
		int x, y, z;	// Kiri Atas
		int cx, cy, cz;	// Titik Tengah untuk rotasi
		float mx, my, mz;

		// Multiplication
		float k;

		// Rotation
		float degreeX, degreeY, degreeZ;

		// Wireframe
		int *original;
		float *wireframe;
		int len;

		int wireRed;
		int wireGreen;
		int wireBlue;

		// Scanline		
		int nLine;

		int fillRed;
		int fillGreen;
		int fillBlue;

		// Private Methods
		int *intdup(int const * src, size_t len);

		// Bresenham algorithm
		int iabs(int n);
		int F(int X, int Y, int Z);// Z bukan untuk 3D
		int G(int X, int Y);

	public:
		Polygon(int cx, int cy, int cz, int*, int len);
		~Polygon();

		int getX();
		int getY();
		int getZ();
		void setPosition(int, int, int);

		int getCX();
		int getCY();
		int getCZ();
		void setCenter(int, int, int);

		void setMultiplication(float);		
		float getMultiplication();

		void setDegree(float, int);
		float getDegreeX();
		float getDegreeY();
		float getDegreeZ();

		void computeMiddle();

		void setWireframe(int*, int);

		void setWireColor(int r, int g, int b);
		void setFillColor(int, int, int);

        int getLineX1(int);
        int getLineY1(int);
        int getLineZ1(int);
        int getLineX2(int);
        int getLineY2(int);
        int getLineZ2(int);

		int getFillRed();
		int getFillGreen();
		int getFillBlue();

        
        int getNLine();

        static bool isBehind(Polygon* a, Polygon* b);
        static bool isFront(Polygon* a, Polygon* b);
};