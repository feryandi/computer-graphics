#pragma once

#include "polygon.class.h"

class object {

private:

	polygon *polygons;
	int nPolygon;

	int centerX, centerY;

	int X;
	int Y;
	int vY;
	int vX;
	int aY;
	int aX;

	int Scale = 1;
	int vScale;
	int aScale;

public:

	object() {}
	~object() { delete[] polygons; }

	void init(int **_polyline, int _nPolygon);
	void draw(frameBuffer *f);


	void objectRoutine() {
		X += vX;
		vX += aX;
		Y += vY;
		vY += aY;
		Scale += vScale;
		vScale += aScale;
	}
	
	void setCenter(int _centerX, int _centerY) {
		centerX = _centerX; centerY = _centerY;
	}
	void setPosition(int _x, int _y) {
		X = _x; Y = _y;
	}
	void setVelocity(int _vx, int _vy) {
		vX = _vx; vY = _vy;
	}
	void setAcceleration(int _ax, int _ay) {
		aX = _ax; aY = _ay;
	}
};


void object::init(int **polyline, int _nPolygon){
	
	nPolygon = _nPolygon;

	polygons = new polygon[nPolygon];

	for (int i=0; i<nPolygon; i++) {
		polygons[i].setPolyline(polyline[i], sizeof(*polyline)/16);
		polygons[i].setCenterX(centerX);
		polygons[i].setCenterY(centerY);
	}

}

void object::draw(frameBuffer *f) {

	for (int i=0; i<nPolygon; i++) {
		polygons[i].setMultiplication(Scale);
		polygons[i].setPosition(X,Y);
		polygons[i].setFloodPosition(2, 2);
		polygons[i].draw(f);
	}

}