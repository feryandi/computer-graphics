#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "frameBuffer.class.h"
#include "polygon.class.h"

#include <vector>

polygon::polygon() {
	x = 0;
	y = 0;
	fx = 0;
	fy = 0;
	width = 0;
	height = 0;
	multiplication = 1;
}

polygon::~polygon() {
	delete [] polyline;
}

int polygon::getPositionX() {
	return x;
}

int polygon::getPositionY() {
	return y;
}

void polygon::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void polygon::setFloodPosition(int x, int y) {
	this->fx = x;
	this->fy = y;
}

void polygon::setWidth(int w) {
	width = w;
}

void polygon::setHeight(int h) {
	height = h;
}

void polygon::setPolyline(int* p, int size) {
/* printf("%d", (int)(sizeof(*p)));
   printf("%d", sizeof(&p));*/
    polyline = new int[(size*4)+1];

    for (int i = 0; i < size*4; i++) {
    	*(polyline + i) = p[i];   	
    }
    nLine = size;
    
    oosMap = (int**) malloc(size*sizeof(int*));
}

void polygon::setFillColor(int r, int g, int b){
	fillRed = r;
	fillGreen = g;
	fillBlue = b;
}


void polygon::setMultiplication(int m) {
	multiplication = m;
}

int polygon::iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}


void polygon::clearMap(){
	for (int i = 0; i < nLine; ++i)
		free(oosMap[i]);
}

int polygon::isIntersect(int e, int yScanline){
	int y1E = *(polyline + (e<<2) + 1) * multiplication + y;
	int y2E = *(polyline + (e<<2) + 3) * multiplication + y;

	return ((y1E - yScanline)*(y2E -yScanline)) <= 0;
}

int polygon::isHorizontalLine(int e){
	int y1E = *(polyline + (e<<2) + 1);
	int y2E = *(polyline + (e<<2) + 3);

	return (y1E == y2E);
}

int polygon::getMiddleX(int e){
	int x1E = *(polyline + (e<<2) + 0) * multiplication + x;
	int x2E = *(polyline + (e<<2) + 2) * multiplication + x;

	return (x1E + x2E) >> 1;
}

int polygon::isCriticalPoint(int e1, int e2, int yScanline){
	int y1E1 = *(polyline + (e1<<2) + 1) * multiplication + y;
	int y2E1 = *(polyline + (e1<<2) + 3) * multiplication + y;
	int y1E2 = *(polyline + (e2<<2) + 1) * multiplication + y;
	int y2E2 = *(polyline + (e2<<2) + 3) * multiplication + y;

	int yOuterE1 = y1E1 + y2E1 - yScanline;
	int yOuterE2 = y1E2 + y2E2 - yScanline;

	return ((yOuterE1 - yScanline)*(yOuterE2 - yScanline)) >= 0;
}

int polygon::xIntersect(int e, int yScanline){
	int y1E = *(polyline + (e<<2) + 1) * multiplication + y;

	return oosMap[e][iabs(yScanline - y1E)];
}

void polygon::fill(int yMin, int yMax, frameBuffer *f){
	
	for (int yScanline = yMin; yScanline <= yMax; ++yScanline) {
		
		//printf("[ y = %d ] ", yScanline);


		std::vector<intersection> intersectEdge; 
		for (int e = 0; e < nLine; ++e) {
			if (isIntersect(e, yScanline)) {
				int type = isHorizontalLine(e);
				int x;
				if (type) {
					x = getMiddleX(e);
				} else {
					x = xIntersect(e, yScanline);
				}
				intersectEdge.push_back(intersection(e, x, type));
			}
		}

		std::sort(intersectEdge.begin(), intersectEdge.end());

		//filter
		std::vector<intersection>::iterator i = intersectEdge.begin(), j;

		if (i!=intersectEdge.end()) {
			while ( (i+1) != intersectEdge.end()) {
				if ((((i+1)->x - i->x) < 5) &&
					(!isCriticalPoint((*i).edge,(*(i+1)).edge, yScanline))) {
					
					printf("!critical x1:%d x2:%d (c: %d)\n", (*(i)).x, (*(i+1)).x, (((i+1)->x - i->x)));
					i = intersectEdge.erase(i);

				} else {
					if ((i+1)->type == 1) {
						if (isCriticalPoint((*i).edge,(*(i+2)).edge, yScanline)) {
							i++;
							i = intersectEdge.erase(i);
						} else {
							i++;
							i->x = (i+1)->x;
							i++;
						}
					} else {
						i++;
					}
				}
			}
		}

		for (int i = 0; i+1 < intersectEdge.size(); i+=2) {
			int e = intersectEdge[i].edge;
			// int x1E = *(polyline + (e<<2) + 0) * multiplication + y;
			// int y1E = *(polyline + (e<<2) + 1) * multiplication + y;
			// int x2E = *(polyline + (e<<2) + 2) * multiplication + y;
			// int y2E = *(polyline + (e<<2) + 3) * multiplication + y;
			//printf("%d [(%d, %d)->(%d, %d)] (x: %d, type: %d) ", intersectEdge[i].edge, x1E, y1E, x2E, y2E, intersectEdge[i].x, intersectEdge[i].type);
			for (int x = intersectEdge[i].x; x < intersectEdge[i+1].x; x++) {
				(*f).blockBuilder(x, yScanline, 1, fillRed,fillGreen,fillBlue);
			}
		}



		printf("\n");
	}
}

void polygon::draw(frameBuffer *f) {
	int line = 0;

	int yMax = *(polyline + 1);
	int yMin = *(polyline + 1);

	while (line < nLine) {
		int x1, y1, x2, y2;

		x1 = *(polyline + (line << 2 | 0)) * multiplication + x;
		y1 = *(polyline + (line << 2 | 1)) * multiplication + y;
		x2 = *(polyline + (line << 2 | 2)) * multiplication + x;
		y2 = *(polyline + (line << 2 | 3)) * multiplication + y;

		if (yMax < std::max(y1,y2)) yMax = std::max(y1,y2);
		if (yMin > std::min(y1,y2)) yMin = std::min(y1,y2);

		//printf("-- bressenham e: %d --\n", line);

		(*f).bresenham(x1, y1, x2, y2, 1, 0, 0, 0, &oosMap[line]);

		line++;
	}

	//printf("------------ (yMin: %d, yMax: %d) ----------------\n", yMin, yMax);
	fill(yMin, yMax, f);


	clearMap();

	//(*f).floodFill(fx*multiplication + x, fy*multiplication + y);
	//(*f).floodFill(5, 5);
}
