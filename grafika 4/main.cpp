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
#include "transformation.h"
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

int rightWing[] = {
				45, 18, 48, 17,
				48, 17, 52, 17,
				52, 17, 60, 18,
				60, 18, 68, 20,
				68, 20, 71, 22,
				71, 22, 72, 24,
				72, 24, 71, 26,
				71, 26, 68, 28,
				68, 28, 60, 30,
				60, 30, 52, 31,
				52, 31, 48, 31,
				48, 31, 45, 30,
				45, 30, 46, 24,
				46, 24, 45, 18
};

//harus digambar terakhir
int frontBody[] = {
				38, 18, 42, 20,
				42, 20, 44, 24,
				44, 24, 42, 28,
				42, 28, 38, 30,
				38, 30, 34, 28,
				34, 28, 32, 24,
				32, 24, 34, 20,
				34, 20, 38, 18
};

//harus digambar sebelum frontBody
int secondFrontBody[] = {
				38, 16, 42, 17,
				42, 17, 45, 20,
				45, 20, 46, 24,
				46, 24, 45, 28,
				45, 28, 42, 31,
				42, 31, 38, 32,
				38, 32, 34, 31,
				34, 31, 31, 28,
				31, 28, 30, 24,
				30, 24, 31, 20,
				31, 20, 34, 17,
				34, 17, 38, 16
};

//harus digambar sebelum second front body
int body[] = {
				30, 24, 31, 18,
				31, 18, 32, 16,
				32, 16, 34, 13,
				34, 13, 36, 12,
				36, 12, 40, 12,
				40, 12, 42, 13,
				42, 13, 44, 16,
				44, 16, 45, 18,
				45, 18, 46, 24,
				46, 24, 45, 30,
				45, 30, 44, 34,
				44, 34, 46, 38,
				46, 38, 44, 39,
				44, 39, 42, 35,
				42, 35, 34, 35,
				34, 35, 32, 39,
				32, 39, 30, 38,
				30, 38, 32, 34,
				32, 34, 31, 30,
				31, 30, 30, 24
};

int leftTyre[] = {
				30, 38, 32, 39,
				32, 39, 32, 41,
				32, 41, 30, 45,
				30, 45, 28, 46,
				28, 46, 26, 45,
				26, 45, 26, 43,
				26, 43, 28, 39,
				28, 39, 30, 38
};

int rightTyre[] = {
				46, 38, 48, 39,
				48, 39, 50, 43,
				50, 43, 50, 45,
				50, 45, 48, 46,
				48, 46, 46, 45,
				46, 45, 44, 41,
				44, 41, 44, 39,
				44, 39, 46, 38
};

int tail[] = {
				26, 14, 36, 14,
				36, 14, 37, 2,
				37, 2, 38, 1,
				38, 1, 39, 2,
				39, 2, 40, 14,
				40, 14, 50, 14,
				50, 14, 48, 16,
				48, 16, 28, 16,
				28, 16, 26,  14
};


// Paling akhir
int propeller[] = {
				12, 0, 37, 12,
				37, 12, 37, 25,
				37, 25, 50, 38,
				50, 38, 62, 50,
				62, 50, 37, 38,
				37, 38, 37, 25,
				37, 25, 12, 0
};

int degree = 0;
polygon p1,p2,p3,p4,p5,p6,p7,p8,p9;

void drawPlane(int positionX, int positionY, int multiply, frameBuffer *f) {


// int rightPropeller[] = {
// 	38, 24, 52, 20,
// 	52, 20, 52, 24,
// 	52, 24, 38, 24
// };
//
// int leftPropeller[] = {
// 	38, 24, 24, 24,
// 	24, 24, 24, 28,
// 	24, 28, 38, 24
// };
//
//
// void drawPlane(int positionX, int positionY, int multiply, frameBuffer *f) {
// 	polygon p1, p2, p3, p4, p5, p6, p7, p8;

	p1.setMultiplication(multiply);
	p1.setCenterX(38);
	p1.setCenterY(24);
	p1.setPolyline(leftWing, 14);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setCenterX(38);
	p2.setCenterY(24);
	p2.setPolyline(rightWing, 14);
	p2.setPosition(positionX, positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setCenterX(38);
	p3.setCenterY(24);
	p3.setPolyline(leftTyre, 8);
	p3.setPosition(positionX,positionY);
	p3.setFloodPosition(2, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setCenterX(38);
	p4.setCenterY(24);
	p4.setPolyline(rightTyre, 8);
	p4.setPosition(positionX,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);

	p5.setMultiplication(multiply);
	p5.setCenterX(38);
	p5.setCenterY(24);
	p5.setPolyline(tail, 9);
	p5.setPosition(positionX,positionY);
	p5.setFloodPosition(2, 2);
	p5.draw(f);

	p6.setMultiplication(multiply);
	p6.setCenterX(38);
	p6.setCenterY(24);
	p6.setPolyline(body, 20);
	p6.setPosition(positionX,positionY);
	p6.setFloodPosition(2, 2);
	p6.draw(f);

	p7.setMultiplication(multiply);
	p7.setCenterX(38);
	p7.setCenterY(24);
	p7.setPolyline(secondFrontBody, 12);
	p7.setPosition(positionX,positionY);
	p7.setFloodPosition(2, 2);
	p7.draw(f);

	p8.setMultiplication(multiply);
	p8.setCenterX(38);
	p8.setCenterY(24);
	p8.setPolyline(frontBody, 8);
	p8.setPosition(positionX,positionY);
	p8.setFloodPosition(2, 2);
	p8.draw(f);

	p9.setMultiplication(multiply);
	int * newPropeller = rotateList(degree, 37, 25, propeller, 28);
	p9.setPolyline(newPropeller, 7);
	p9.setCenterX(38);
	p9.setCenterY(25);
	// printf("%d\n", propeller[1]);
	p9.setPosition(positionX,positionY);
	p9.setFloodPosition(2, 2);
	p9.draw(f);
}


// =======
// int *intdup(int const * src, size_t len)
// {
//    int * p = (int*)malloc(len * sizeof(int));
//    memcpy(p, src, len * sizeof(int));
//    return p;
// }
// >>>>>>> fc67277d907511164acab1761f488e4b82213328
//
// void printArray(int array[], int len){
// 	for (int i =0; i < len; i++){
// 		printf("%d, ", array[i]);
// 	}
// 	printf("\n");
// }
//
// void drawPropeller(int degree, int positionX, int positionY, int multiply, frameBuffer *f){
// 	polygon p1, p2;
//
// 	p1.setMultiplication(multiply);
// 	p1.setCenterX(38);
// 	p1.setCenterY(24);
// 	int * newRightPropeller = rotateList(degree, 38, 24, rightPropeller, 12);
// 	//printf("old ");
// 	//printArray(rightPropeller,12);
// 	//printf("new ");
// 	//printArray(newRightPropeller,12);
// 	p1.setPolyline(newRightPropeller, 3);
// 	p1.setPosition(positionX,positionY);
// 	p1.setFloodPosition(2, 2);
// 	p1.draw(f);
//
// 	p2.setMultiplication(multiply);
// 	p2.setCenterX(38);
// 	p2.setCenterY(24);
// 	int* newLeftPropeller = rotateList(degree, 38, 24, leftPropeller, 12);
// 	p2.setPolyline(newLeftPropeller, 3);
// 	p2.setPosition(positionX,positionY);
// 	p2.setFloodPosition(2, 2);
// 	p2.draw(f);
// }
//
// int abs(int n) {
// 	if (n < 0) {
// 		n *= -1;
// 	}
// 	return n;
// }

void destroy(frameBuffer *f){

	int reductor = 0;
	while (reductor < 1000) {

		p1.setMultiplication(p1.getMultiplication());
		p1.setCenterX(38);
		p1.setCenterY(24);
		p1.setPolyline(leftWing, 14);
		p1.setPosition(p1.getPositionX()-reductor, p1.getPositionY());
		p1.setFloodPosition(2, 2);
		p1.draw(f);

		p2.setMultiplication(p2.getMultiplication());
		p2.setCenterX(38);
		p2.setCenterY(24);
		p2.setPolyline(rightWing, 14);
		p2.setPosition(p2.getPositionX()+reductor, p2.getPositionY());
		p2.setFloodPosition(2, 2);
		p2.draw(f);

		p3.setMultiplication(p3.getMultiplication());
		p3.setCenterX(38);
		p3.setCenterY(24);
		p3.setPolyline(leftTyre, 8);
		p3.setPosition(p3.getPositionX(),p3.getPositionY()+reductor);
		p3.setFloodPosition(2, 2);
		p3.draw(f);

		p4.setMultiplication(p4.getMultiplication());
		p4.setCenterX(38);
		p4.setCenterY(24);
		p4.setPolyline(rightTyre, 8);
		p4.setPosition(p4.getPositionX(),p4.getPositionY()+reductor);
		p4.setFloodPosition(2, 2);
		p4.draw(f);

		p5.setMultiplication(p5.getMultiplication());
		p5.setCenterX(38);
		p5.setCenterY(24);
		p5.setPolyline(tail, 9);
		p5.setPosition(p5.getPositionX()+reductor,p5.getPositionY()+reductor);
		p5.setFloodPosition(2, 2);
		p5.draw(f);

		p6.setMultiplication(p6.getMultiplication());
		p6.setCenterX(38);
		p6.setCenterY(24);
		p6.setPolyline(body, 20);
		p6.setPosition(p6.getPositionX()-reductor,p6.getPositionY()-reductor);
		p6.setFloodPosition(2, 2);
		p6.draw(f);

		p7.setMultiplication(p7.getMultiplication());
		p7.setCenterX(38);
		p7.setCenterY(24);
		p7.setPolyline(secondFrontBody, 12);
		p7.setPosition(p7.getPositionX()+reductor,p7.getPositionY()-reductor);
		p7.setFloodPosition(2, 2);
		p7.draw(f);

		p8.setMultiplication(p8.getMultiplication());
		p8.setCenterX(38);
		p8.setCenterY(24);
		p8.setPolyline(frontBody, 8);
		p8.setPosition(p8.getPositionX()-reductor,p8.getPositionY()-reductor);
		p8.setFloodPosition(2, 2);
		p8.draw(f);

		p9.setMultiplication(p9.getMultiplication());
		int * newPropeller = rotateList(degree, 37, 25, propeller, 28);
		p9.setPolyline(newPropeller, 7);
		p9.setCenterX(38);
		p9.setCenterY(25);
		// printf("%d\n", propeller[1]);
		p9.setPosition(p9.getPositionX(),p9.getPositionY()+reductor);
		p9.setFloodPosition(2, 2);
		p9.draw(f);

		f->render_buffer();
		degree = (degree + 5) % 360;
		f->solidBackground();
		reductor = (reductor+8)/2;
	}
}

int main() {
	frameBuffer f;
	f.solidBackground();

	int reductor = 0;
	int reductorFall = 0;
	int i = 1;
	int isPlus = 0;

	while (reductor < 500) {
		// drawPlane(0,f.getVInfoY()-reductor,5,&f);
			drawPlane(f.getVInfoX()-(reductor*2),f.getVInfoY()-400-reductor/2,reductor/50,&f);



		// if (reductor > f.getVInfoY() + 300){
		// =======
// 	int degree = 0;
// 	float scale = 1;
// 	int penambah = 1;
// 	while (reductor < f.getVInfoX() + 20*5 - 100) {
// 		drawPlane(f.getVInfoX()-reductor,100,scale,&f);
// 		if(reductor<f.getVInfoX()/2){
// 			drawPropeller(degree,f.getVInfoX()-reductor,100,scale,&f);
// 		}else{
// 			drawPropeller(degree,f.getVInfoX()/2,100+reductorFall,scale,&f);
// 			reductorFall++;
// 		}
// >>>>>>> fc67277d907511164acab1761f488e4b82213328
		f.render_buffer();
		degree = (degree + 5) % 360;
		++reductor;
		// degree++;
		// degree = degree%360;
		// penambah++;
		//if(reductor>100)
		// scale = scale + 0.00005;
		f.solidBackground();
	}
	destroy(&f);
}
