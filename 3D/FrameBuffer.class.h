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
#include <vector>
#include <time.h>

#include "Polygon.class.h"

class FrameBuffer {
	private:
		// Default Things
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;

		int fbfd;
		long int screensize;
		char *fbp;
		long int location;

		// Making Render Smoother
		char *buffer;

		// Private Methods
		void drawPolygon(Polygon*);

		// bresenham
		int iabs(int n);
		void bresenham(int x1, int y1, int x2, int y2, int red, int green, int blue, int line);
		int F(int X, int Y, int Z); 
		int G(int X, int Y);

		// OOS Scanline algorithm
		int **oosMap;
		void clearMap(Polygon*);
		int isIntersect(Polygon*, int, int);
		int isHorizontalLine(Polygon*, int);
		int getMiddleX(Polygon*, int e);
		int isCriticalPoint(Polygon*, int, int, int);
		int xIntersect(Polygon*, int, int);

		void fillPolygon(Polygon* polygon, int yMin, int yMax);
	
	public:
		FrameBuffer();
		~FrameBuffer();

		int getVInfoY();
		int getVInfoX();

		//void addPolygon(Polygon*);
		void addObject(); // To Be Implemented


		void canvas();
		void plot(int x, int y, int, int, int);
		void render();

		void draw(std::vector<Polygon*>&);

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


inline bool operator> (FrameBuffer::intersection &i1, FrameBuffer::intersection &i2) {
    return i1.x > i2.x;
}

inline bool operator< (FrameBuffer::intersection &i1, FrameBuffer::intersection &i2) {
    return i1.x < i2.x;
}
