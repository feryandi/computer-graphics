#ifndef polygon_Class_H
#define polygon_Class_H
#include "frameBuffer.class.h"

class polygon {
	private:
		int x;
		int y;
		int width;
		int height;
		int multiplication;
		int *polyline;
		int lines;
	
	public:
		polygon();
		~polygon();
		void setPosition(int, int);
		void setWidth(int);
		void setHeight(int);
		void setPolyline(int*, int);
		void setMultiplication(int);
		void draw(frameBuffer*);
};

#endif