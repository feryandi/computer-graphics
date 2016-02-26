#ifndef polygon_Class_H
#define polygon_Class_H
#include "frameBuffer.class.h"

class polygon {
	private:
		int x;
		int y;
		int fx;
		int fy;
		int width;
		int height;
		float multiplication;
		int *polyline;
		int lines;
		int centerX;
		int centerY;

	public:
		polygon();
		~polygon();
		int getPositionX();
		int getPositionY();
		void setPosition(int, int);
		void setFloodPosition(int, int);
		void setWidth(int);
		void setHeight(int);
		void setPolyline(int*, int);
		void setMultiplication(float);
		float getMultiplication();
		void setCenterX(int);
		void setCenterY(int);
		void draw(frameBuffer*);
};

#endif
