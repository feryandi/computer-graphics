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
#include "frameBuffer.class.h"
#include "polygon.class.h"

polygon::polygon() {
	x = 0;
	y = 0;
	cx = 0;
	cy = 0;
	fx = 0;
	fy = 0;
	isFill = 0;
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

int polygon::getMultiplication(){
	return multiplication;
}

int polygon::getCenterX() {
	return cx;
}

int polygon::getCenterY() {
	return cy;
}

void polygon::setIsFill(int i) {
	this->isFill = i;
}

void polygon::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void polygon::setCenter(int cx, int cy) {
	this->cx = cx;
	this->cy = cy;
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
    lines = size * 4;
}

void polygon::setMultiplication(int m) {
	multiplication = m;
}

void polygon::solidFill(int xs, int ys, int xe, int ye, frameBuffer *f) {
	(*f).solidFill((xs-cx) * multiplication + x, (ys-cy)* multiplication + y, (xe-cx) * multiplication + x, (ye-cy) * multiplication + y, 0, 0, 0);
}

void polygon::draw(frameBuffer *f) {
	int i = 0;
	while (i < lines) {
		int a, b, c, d;
		a = (*(polyline + (++i) - 1)-cx) * multiplication + x;
		b = (*(polyline + (++i) - 1)-cy) * multiplication + y;
		c = (*(polyline + (++i) - 1)-cx) * multiplication + x;
		d = (*(polyline + (++i) - 1)-cy) * multiplication + y;

		(*f).bresenham(a, b, c, d, 1, 0, 0, 0);
	}

	if (isFill == 1) {
		//(*f).floodFill(fx*multiplication + x, fy*multiplication + y, 10, 255, 255);
	}
}
