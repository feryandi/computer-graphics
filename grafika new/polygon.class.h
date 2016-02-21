#ifndef polygon_Class_H
#define polygon_Class_H
#include "frameBuffer.class.h"

class polygon {
	private:
		int x;
		int y;
		int cx;
		int cy;
		int fx;
		int fy;
		int isFill;
		int width;
		int height;
		int multiplication;
		int *polyline;
		int lines;
		
		// Dot List
		int yMax;
		int yMin;
	
	public:
		polygon();
		~polygon();
		int getPositionX();
		int getPositionY();
		int getMultiplication();
		int getCenterX();
		int getCenterY();
		void setIsFill(int i);
		void setPosition(int, int);
		void setCenter(int, int);
		void setFloodPosition(int, int);
		void setWidth(int);
		void setHeight(int);
		void setPolyline(int*, int);
		void setMultiplication(int);
		void solidFill(int xs, int ys, int xe, int ye, frameBuffer *f);
		void draw(frameBuffer*);
};

#endif