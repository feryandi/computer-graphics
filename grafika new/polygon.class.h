#pragma once

#include "frameBuffer.class.h"

class polygon {
	private:
		int x;
		int y;
		int cx;
		int cy;
		int fx;
		int fy;
		int width;
		int height;
		int multiplication;
		int *polyline;
		int nLine;
		int **oosMap;

		int fillRed;
		int fillGreen;
		int fillBlue;


		void clearMap();
		int isCriticalPoint(int, int, int);
		int isIntersect(int, int);
		int isHorizontalLine(int);
		int xIntersect(int, int);
		int getMiddleX(int e);

		void fill(int, int, frameBuffer*);


	public:
		polygon();
		~polygon();
		int getPositionX();
		int getPositionY();
		int getCenterX();
		int getCenterY();
		void setPosition(int, int);
		void setFloodPosition(int, int);
		void setWidth(int);
		void setHeight(int);
		void setPolyline(int*, int);
		void setMultiplication(int);
		void setFillColor(int, int, int);
		void drawNoFill(frameBuffer*);
		void draw(frameBuffer*);
		float getMultiplication();
		void setCenter(int, int);
		int iabs(int n);
		void solidFill(int xs, int ys, int xe, int ye, frameBuffer *f);

		class intersection
        {
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

inline bool operator> (polygon::intersection &i1, polygon::intersection &i2) {
    return i1.x > i2.x;
}

inline bool operator< (polygon::intersection &i1, polygon::intersection &i2) {
    return i1.x < i2.x;
}
