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
#include "plane.class.h"
#include "transformation.c"
#include "frameBuffer.class.h"
#include <iostream>
using namespace std;

int rightPropeller[] = {
	38, 24, 52, 20, 
	52, 20, 52, 24, 
	52, 24, 38, 24
};

int leftPropeller[] = {
	38, 24, 24, 24, 
	24, 24, 24, 28, 
	24, 28, 38, 24
};


int *intdup(int const * src, size_t len)
{
   int * p = (int*)malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}

void printArray(int array[], int len){
	for (int i =0; i < len; i++){
		printf("%d, ", array[i]);
	}
	printf("\n");
}

void drawPropeller(int degree, int positionX, int positionY, float multiply, frameBuffer *f){
	polygon p1, p2;

	p1.setMultiplication(multiply);
	p1.setCenterX(38);
	p1.setCenterY(24);
	int * newRightPropeller = rotateList(degree, 38, 24, rightPropeller, 12);
	//printf("old ");
	//printArray(rightPropeller,12);
	//printf("new ");
	//printArray(newRightPropeller,12);
	p1.setPolyline(newRightPropeller, 3);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setCenterX(38);
	p2.setCenterY(24);
	int* newLeftPropeller = rotateList(degree, 38, 24, leftPropeller, 12);
	p2.setPolyline(newLeftPropeller, 3);
	p2.setPosition(positionX,positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);	
}

int abs(int n) {
	if (n < 0) {
		n *= -1;
	}
	return n;
}

int main() {
	frameBuffer f;
	f.solidBackground();

	int reductor = 0;
	int reductorFall = 0;
	int i = 1;
	int isPlus = 0;
	int degree = 0;
	float scale = 1;
	int penambah = 1;

	int propellerX;
	int propellerY;

	float gravity = 0.025;

	plane *a = new plane();
	a->setPosition(f.getVInfoX()/2, 100);
	a->setVelocity(0,0);
	a->setAcceleration(0,0);

	while (1) {
		a->draw(&f);
		f.solidBackground();
	}
	
}
