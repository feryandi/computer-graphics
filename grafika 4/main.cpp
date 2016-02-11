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
#include "transformation.c"
#include "frameBuffer.class.h"
#include "polygon.class.h"
#include <iostream>
using namespace std;
	
// 11
int fontA[] = { 6, 0, 10, 0,
				10, 0, 16, 20,
				16, 20, 12, 20,
				12, 20, 10, 14,
				10, 14, 6, 14,
				6, 14, 4, 20,
				4, 20, 0, 20,
				0, 20, 6, 0,
				8, 7, 9, 10,
				9, 10, 7, 10,
				7, 10, 8, 7};	
// 25
int fontB[] = { 0, 0, 12, 0,
				12, 0, 14, 1,
				14, 1, 15, 2,
				15, 2, 16, 5,
				16, 5, 15, 8,
				15, 8, 13, 10,
				13, 10, 15, 12,
				15, 12, 16, 15,
				16, 15, 15, 18,
				15, 18, 14, 19,
				14, 19, 12, 20,
				12, 20, 0, 20,
				0, 20, 0, 0,
				4, 4, 10, 4,
				10, 4, 11, 5,
				11, 5, 11, 7,
				11, 7, 9, 8,
				9, 8, 4, 8,
				4, 8, 4, 4,
				4, 12, 9, 12,
				9, 12, 11, 13,
				11, 13, 11, 15,
				11, 15, 10, 16,
				10, 16, 4, 16,
				4, 16, 4, 12 };
// 30		
int fontC[] = { 6, 0, 10, 0,
				10, 0, 13, 1,
				13, 1, 15, 3,
				15, 3, 16, 6, 
				16, 6, 16, 8,
				16, 8, 12, 8,
				12, 8, 11, 5,
				11, 5, 10, 4,
				10, 4, 6, 4,
				6, 4, 5, 5,
				5, 5, 4, 8,
				4, 8, 4, 12,
				4, 12, 5, 15,
				5, 15, 6, 16,
				6, 16, 10, 16,
				10, 16, 11, 15,
				11, 15, 12, 12,
				12, 12, 16, 12,
				16, 12, 16, 14,
				16, 14, 15, 17,
				15, 17, 13, 19,
				13, 19, 10, 20,
				10, 20, 6, 20,
				6, 20, 3, 19,
				3, 19, 1, 17,
				1, 17, 0, 14,
				0, 14, 0, 6,
				0, 6, 1, 3,
				1, 3, 3, 1,
				3, 1, 6, 0};	
// 18
int fontD[] = { 0, 0, 8, 0,
				8, 0, 12, 1,
				12, 1, 15, 3,
				15, 3, 16, 6,
				16, 6, 16, 14,
				16, 14, 15, 17,
				15, 17, 12, 19,
				12, 19, 8, 20,
				8, 20, 0, 20,
				0, 20, 0, 0,
				4, 4, 8, 4,
				8, 4, 11, 5,
				11, 5, 12, 8,
				12, 8, 12, 12,
				12, 12, 11, 15,
				11, 15, 8, 16,
				8, 16, 4, 16,
				4, 16, 4, 4 };		
// 12
int fontE[] = { 0, 0, 16, 0,
				16, 0, 16, 4,
				16, 4, 4, 4,
				4, 4, 4, 8,
				4, 8, 12, 8,
				12, 8, 12, 12,
				12, 12, 4, 12,
				4, 12, 4, 16,
				4, 16, 16, 16,
				16, 16, 16, 20,
				16, 20, 0, 20,
				0, 20, 0, 0 };
// 10
int fontF[] = { 0, 0, 16, 0,
				16, 0, 16, 4,
				16, 4, 4, 4,
				4, 4, 4, 8,
				4, 8, 12, 8,
				12, 8, 12, 12,
				12, 12, 4, 12,
				4, 12, 4, 20,
				4, 20, 0, 20,
				0, 20, 0, 0};
// 12
int fontM[] = { 0, 0, 4, 0,
				4, 0, 12, 12,
				12, 12, 20, 0,
				20, 0, 24, 0,
				24, 0, 24, 20,
				24, 20, 20, 20,
				20, 20, 20, 8,
				20, 8, 12, 20,
				12, 20, 4, 8,
				4, 8, 4, 20,
				4, 20, 0, 20,
				0, 20, 0, 0 };
// 10
int fontN[] = { 0, 0, 4, 0,
				4, 0, 12, 12,
				12, 12, 12, 0,
				12, 0, 16, 0,
				16, 0, 16, 20,
				16, 20, 12, 20,
				12, 20, 4, 8,
				4, 8, 4, 20,
				4, 20, 0, 20,
				0, 20, 0, 0 };
// 12
int fontH[] = {	0, 0, 4, 0,
				4, 0, 4, 8,
				4, 8, 12, 8,
				12, 8, 12, 0,
				12, 0, 16, 0,
				16, 0, 16, 20,
				16, 20, 12, 20,
				12, 20, 12, 12,
				12, 12, 4, 12,
				4, 12, 4, 20,
				4, 20, 0, 20,
				0, 20, 0, 0};
// 4
int fontI[] = { 6, 0, 10, 0,
				10, 0, 10, 20,
				10, 20, 6, 20,
				6, 20, 6, 0};
// 9
int fontL[] = { 0, 0, 4, 0,
				4, 0, 4, 4,
				4, 4, 4, 8,
				4, 8, 4, 12,
				4, 12, 4, 16,
				4, 16, 16, 16,
				16, 16, 16, 20,
				16, 20, 0, 20,
				0, 20, 0, 0 };
// 16
int fontJ[] = { 0, 12, 4, 12,
				4, 12, 4, 15,
				4, 15, 5, 16,
				5, 16, 11, 16,
				11, 16, 12, 15,
				12, 15, 12, 0,
				12, 0, 16, 0,
				16, 0, 16, 16,
				16, 16, 15, 18,
				15, 18, 14, 19,
				14, 19, 12, 20,
				12, 20, 4, 20,
				4, 20, 2, 19,
				2, 19, 1, 18,
				1, 18, 0, 16,
				0, 16, 0, 12 };
// 30	
int fontO[] = { 6, 0, 10, 0,
				10, 0, 13, 1,
				13, 1, 15, 3,
				15, 3, 16, 6, 
				16, 6, 16, 8,
				16, 8, 16, 12,
				12, 8, 11, 5,
				11, 5, 10, 4,
				10, 4, 6, 4,
				6, 4, 5, 5,
				5, 5, 4, 8,
				4, 8, 4, 12,
				4, 12, 5, 15,
				5, 15, 6, 16,
				6, 16, 10, 16,
				10, 16, 11, 15,
				11, 15, 12, 12,
				12, 12, 12, 8,
				16, 12, 16, 14,
				16, 14, 15, 17,
				15, 17, 13, 19,
				13, 19, 10, 20,
				10, 20, 6, 20,
				6, 20, 3, 19,
				3, 19, 1, 17,
				1, 17, 0, 14,
				0, 14, 0, 6,
				0, 6, 1, 3,
				1, 3, 3, 1,
				3, 1, 6, 0};	
// 20
int fontR[] = { 0, 0, 12, 0,
				12, 0, 14, 1,
				14, 1, 15, 2,
				15, 2, 16, 5,
				16, 5, 15, 8,
				15, 8, 13, 10,
				13, 10, 12, 11,
				12, 11, 17, 20,
				17, 20, 12, 20,
				12, 20, 8, 12,
				8, 12, 4, 12,
				4, 12, 4, 20,
				4, 20, 0, 20,
				0, 20, 0, 0,
				4, 4, 10, 4,
				10, 4, 11, 5,
				11, 5, 11, 7,
				11, 7, 9, 8,
				9, 8, 4, 8,
				4, 8, 4, 4 };
// 16
int fontU[] = { 0, 0, 4, 0,
				4, 0, 4, 15,
				4, 15, 5, 16,
				5, 16, 11, 16,
				11, 16, 12, 15,
				12, 15, 12, 0,
				12, 0, 16, 0,
				16, 0, 16, 16,
				16, 16, 15, 18,
				15, 18, 14, 19,
				14, 19, 12, 20,
				12, 20, 4, 20,
				4, 20, 2, 19,
				2, 19, 1, 18,
				1, 18, 0, 16,
				0, 16, 0, 0 };
// 13
int fontW[] = { 0, 0, 5, 0, 
				5, 0, 8, 10,
				8, 10, 11, 0,
				11, 0, 17, 0,
				17, 0, 20, 10,
				20, 10, 23, 0,
				23, 0, 28, 0,
				28, 0, 22, 20,
				22, 20, 18, 20,
				18, 20, 14, 7,
				14, 7, 10, 20,
				10, 20, 6, 20,
				6, 20, 0, 0 };
// 9
int fontY[] = { 0, 0, 4, 0,
				4, 0, 8, 8,
				8, 8, 12, 0,
				12, 0, 16, 0,
				16, 0, 10, 12,
				10, 12, 10, 20,
				10, 20, 6, 20,
				6, 20, 6, 12,
				6, 12, 0, 0};
// 14
int leftWing[] = {
				0, 24, 1, 22,
				1, 22, 4, 20,
				4, 20, 12, 18, 
				12, 18, 20, 17, 
				20, 17, 24, 17, 
				24, 17, 31, 18, 
				31, 18, 30, 24, 
				30, 24, 31, 30, 
				31, 30, 24, 31, 
				24, 31, 20, 31, 
				20, 31, 12, 30, 
				12, 30, 4, 28, 
				4, 28, 1, 26, 
				1, 26, 0, 24};

void makeWawan(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1,p2,p3,p4,p5;
	p1.setMultiplication(multiply);
	p1.setPolyline(fontW, 13);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(5, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setPolyline(fontA, 11);
	p2.setPosition((positionX+29)*multiply, positionY);
	p2.setFloodPosition(8, 2);
	p2.draw(f);
	
	p3.setMultiplication(multiply);
	p3.setPolyline(fontW, 13);
	p3.setPosition((positionX+29+17)*multiply,positionY);
	p3.setFloodPosition(5, 2);
	p3.draw(f);
	
	p4.setMultiplication(multiply);
	p4.setPolyline(fontA, 11);
	p4.setPosition((positionX+29+17+29)*multiply,positionY);
	p4.setFloodPosition(8, 2);
	p4.draw(f);
	
	p5.setMultiplication(multiply);
	p5.setPolyline(fontN, 10);
	p5.setPosition((positionX+29+17+29+19)*multiply,positionY);
	p5.setFloodPosition(2, 2);
	p5.draw(f);
};

void makeJulio(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1,p2,p3,p4,p5;
	p1.setMultiplication(multiply);
	p1.setPolyline(fontJ, 16);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(15, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setPolyline(fontU, 16);
	p2.setPosition((positionX+18)*multiply, positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setPolyline(fontL, 9);
	p3.setPosition((positionX+18+18)*multiply,positionY);
	p3.setFloodPosition(2, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setPolyline(fontI, 4);
	p4.setPosition((positionX+18+18+18)*multiply,positionY);
	p4.setFloodPosition(8, 2);
	p4.draw(f);

	p5.setMultiplication(multiply);
	p5.setPolyline(fontO, 30);
	p5.setPosition((positionX+18+18+18+18)*multiply,positionY);
	p5.setFloodPosition(8, 2);
	p5.draw(f);
};

void makeChaer(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1,p2,p3,p4,p5;
	p1.setMultiplication(multiply);
	p1.setPolyline(fontC, 30);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(8, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setPolyline(fontH, 12);
	p2.setPosition((positionX+18)*multiply, positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setPolyline(fontA, 11);
	p3.setPosition((positionX+18+18)*multiply,positionY);
	p3.setFloodPosition(8, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setPolyline(fontE, 12);
	p4.setPosition((positionX+18+18+18)*multiply,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);

	p5.setMultiplication(multiply);
	p5.setPolyline(leftWing, 14);
	p5.setPosition((positionX+18+18+18+18)*multiply,positionY);
	p5.setFloodPosition(2, 2);
	p5.draw(f);
};

void makeFery(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1,p2,p3,p4;
	p1.setMultiplication(multiply);
	p1.setPolyline(fontF, 10);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setPolyline(fontE, 12);
	p2.setPosition((positionX+18)*multiply, positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setPolyline(fontR, 20);
	p3.setPosition((positionX+18+18)*multiply,positionY);
	p3.setFloodPosition(2, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setPolyline(fontY, 9);
	p4.setPosition((positionX+18+18+18)*multiply,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);
};

void makeAdin(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1,p2,p3,p4;
	p1.setMultiplication(multiply);
	p1.setPolyline(fontA, 11);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(8, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setPolyline(fontD, 18);
	p2.setPosition((positionX+18)*multiply, positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setPolyline(fontI, 4);
	p3.setPosition((positionX+18+18)*multiply,positionY);
	p3.setFloodPosition(8, 2);
	p3.draw(f);
	
	p4.setMultiplication(multiply);
	p4.setPolyline(fontN, 10);
	p4.setPosition((positionX+18+18+18)*multiply,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);
};

void makeBoim(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1,p2,p3,p4;
	p1.setMultiplication(multiply);
	p1.setPolyline(fontB, 25);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setPolyline(fontO, 30);
	p2.setPosition((positionX+18)*multiply, positionY);
	p2.setFloodPosition(8, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setPolyline(fontI, 4);
	p3.setPosition((positionX+18+18)*multiply,positionY);
	p3.setFloodPosition(8, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setPolyline(fontM, 12);
	p4.setPosition((positionX+18+18+18)*multiply,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);
};

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
	int i = 1;
	int isPlus = 0;
	while (reductor < f.getVInfoY() + 20*5 ) {
		makeWawan(0,f.getVInfoY()-reductor,4-abs(4-((f.getVInfoY()-(f.getVInfoY()-reductor))/100)),&f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
		if(reductor>=500){
			translateList(0, 0, fontW, 52);
			translateList(0, 0, fontA, 44);
			translateList(1, 1, fontN, 40);
		}
	}

	reductor = 0;
	while (reductor < f.getVInfoY() + 20*5 ) {
		makeJulio(0,f.getVInfoY()-reductor,4-abs(4-((f.getVInfoY()-(f.getVInfoY()-reductor))/100)),&f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
	}

	reductor = 0;
	while (reductor < f.getVInfoY() + 20*5 ) {
		makeChaer(0,f.getVInfoY()-reductor,4-abs(4-((f.getVInfoY()-(f.getVInfoY()-reductor))/100)),&f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
	}
	
	reductor = 0;
	while (reductor < f.getVInfoY() + 20*5 ) {
		makeFery(0,f.getVInfoY()-reductor,4-abs(4-((f.getVInfoY()-(f.getVInfoY()-reductor))/100)),&f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
	}
	
	reductor = 0;
	while (reductor < f.getVInfoY() + 20*5 ) {
		makeAdin(0,f.getVInfoY()-reductor,4-abs(4-((f.getVInfoY()-(f.getVInfoY()-reductor))/100)),&f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
	}
	
	reductor = 0;
	while (reductor < f.getVInfoY() + 20*5 ) {
		makeBoim(0,f.getVInfoY()-reductor,4-abs(4-((f.getVInfoY()-(f.getVInfoY()-reductor))/100)),&f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
	}

}
