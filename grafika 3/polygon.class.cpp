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
	width = 0;
	height = 0;
	multiplication = 1;
}

polygon::~polygon() {
	delete [] polyline;	
}

void polygon::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void polygon::setWidth(int w) {
	width = w;
}

void polygon::setHeight(int h) {
	height = h;
}

void polygon::setPolyline(int* p, int size) {
/*	int size = (int)(sizeof(&p)/sizeof(*p)) + 1;
    printf("%d", sizeof(&p));*/
    polyline = new int[size*2];

    for (int i = 0; i <= size*2; i++) {
    	*(polyline + i) = p[i];   	
    }
    lines = size;
}

void polygon::setMultiplication(int m) {
	multiplication = m;
}

void polygon::draw(frameBuffer *f) {
	int i = 0;
	while (i < lines) {
		int a, b, c, d;
		a = (*(polyline + (i * 2))) * multiplication + x;
		b = (*(polyline + ((i * 2)+1))) * multiplication + y;
		c = (*(polyline + ((i+1) * 2))) * multiplication + x;
		d = (*(polyline + (((i+1) * 2)+1))) * multiplication + y;

/*		printf("%d-", (i * 2));
		printf("%d-", (i * 2)+1);
		printf("%d-", ((i+1) * 2));
		printf("%d\n", ((i+1) * 2)+1);*/

		(*f).bresenham(a, b, c, d, 1, 0, 0, 0);

		++i;
		/*printf("%d[%d]", i, *(polyline + i - 1));
		printf("%d[%d]", i, *(polyline + (++i) - 1));
		printf("%d[%d]", i, *(polyline + (++i) - 1));
		printf("%d[%d]\n", i, *(polyline + (++i) - 1));*/
	}

	(*f).floodFill(5*multiplication + x, 5*multiplication + y);
}
